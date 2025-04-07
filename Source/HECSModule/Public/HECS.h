#pragma once

#include <sstream>
#include <vector>
#include <memory>

#define MAX_ENTITIES 1000

namespace HECS
{
	/*
	 * Generates an ID for each new type passed in
	 */
	class IDGenerator
	{
		static unsigned Identifier()
		{
			static unsigned value = 0;
			return value++;
		}

	public:
		template<class T>
		static unsigned GetID()
		{
			static const unsigned value = Identifier();
			return value;
		}
	};

	/*
	* Allows us to combine compile-time and runtime polymorphism
	* to store a collection of different component pools. Also a generic
	* interface to allow us to interact with component pools.
	*/
	class ISparseSet
	{
	public:
		virtual ~ISparseSet() = default;
		virtual bool Has(unsigned entity) = 0;
	};

	template <class T>
	class ComponentPool : public ISparseSet
	{
	public:
		ComponentPool()
		{
			for(int i = 0; i < MAX_ENTITIES; i++)
			{
				SparseArray[i] = UINT_MAX;
				EntityPackedArray[i] = UINT_MAX;
			}
		};

		// Check if component pool contains a component of a given entity
		bool Has(unsigned entity) override
		{
			if(entity > MAX_ENTITIES) return false;
			return
				SparseArray[entity] != UINT_MAX
				&&
				EntityPackedArray[SparseArray[entity]] == entity;
		}

		// Get entity component
		T& Lookup(unsigned entity)
		{
			return ComponentPackedArray[SparseArray[entity]];
		}

		// Add entity component
		void Add(unsigned entity, T value)
		{
			if (Has(entity))
			{
				return;
			}

			SparseArray[entity] = NumComponents++;
			EntityPackedArray[SparseArray[entity]] = entity;
			ComponentPackedArray[SparseArray[entity]] = value;
		}

		// Return entire pool of components
		T* GetComponents()
		{
			return ComponentPackedArray;
		}

		// Remove component from entity
		void Remove(unsigned entity)
		{
			if (!Has(entity)) {
				return;
			}

			// Get packed array index of component being removed
			unsigned index = SparseArray[entity];

			NumComponents--;

			// Swap component and entity with the last element in array
			T& component = ComponentPackedArray[index];
			component = ComponentPackedArray[NumComponents];

			unsigned& entityAddress = EntityPackedArray[index];
			entityAddress = EntityPackedArray[NumComponents];

			SparseArray[entityAddress] = index;
			SparseArray[entity] = UINT_MAX;
		}

		std::string EntityArrayToString()
		{
			std::stringstream string;
			string << "[ ";
			for (unsigned i = 0; i < NumComponents; i++)
			{
				string << EntityPackedArray[i] << " ";
			}
			string << "]";
			return string.str();
		}

		unsigned NumComponents = 0;

		unsigned SparseArray[MAX_ENTITIES];
		unsigned EntityPackedArray[MAX_ENTITIES];
		T ComponentPackedArray[MAX_ENTITIES];

	};

	/*
	* Manages entities, components and systems.
	*/
	class World
	{
	public:
		World() = default;

		// Register component
		template <class T>
		void Register()
		{
			unsigned componentId = IDGenerator::GetID<T>();
			ComponentPools.push_back(std::make_unique<ComponentPool<T>>());
		}

		// Check if an entity has a component
		template <class T>
		bool Has(unsigned entity)
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			bool hasComponent = componentPool->Has(entity);

			return hasComponent;
		}

		// Add component to entity
		template <class T>
		void Add(unsigned entity, T value = T())
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			componentPool->Add(entity, value);
		}

		// Remove component
		template <class T>
		void Remove(unsigned entity)
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			componentPool->Remove(entity);
		}

		// Get component from an entity
		template <class T>
		T& Get(unsigned entity)
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			return componentPool->Lookup(entity);
		}

		template <class T>
		T* GetAll()
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			return componentPool->GetComponents();
		}

		// Create a new entity, return it's ID
		unsigned Entity()
		{
			return NumEntities++;
		}

		unsigned GetNumEntities() const
		{
			return NumEntities;
		}

		template <class T>
		ComponentPool<T>* GetComponentPool()
		{
			// Get pointer to component pool, then cast
			ComponentPool<T>* componentPool = static_cast<ComponentPool<T>*>(ComponentPools[IDGenerator::GetID<T>()].get());
			return componentPool;
		}

	private:
		unsigned NumEntities = 0;

		std::vector<std::unique_ptr<ISparseSet>> ComponentPools;
	};

	/*
	 * Scene view lets you filter out by entities which actually have the
	 * components you are interested in.
	 */
	template<class ...ComponentTypes>
	struct View
	{
		// Set up any details we need to initialise an iterator
		View(World* world) : ViewWorld(world)
		{
			(FindSmallestComponentPool<ComponentTypes>(), ...);
		}

		template <class T>
		void FindSmallestComponentPool() 
		{
			ComponentPool<T>* pool = ViewWorld->GetComponentPool<T>();
			if (SmallestCount > pool->NumComponents)
			{
				SmallestCount = pool->NumComponents;
				EntityArray = pool->EntityPackedArray;
			}
		}

		World* ViewWorld = nullptr;
		unsigned* EntityArray = nullptr;
		unsigned SmallestCount = MAX_ENTITIES;

		struct Iterator
		{
			Iterator(World* world, unsigned* entityArray, unsigned index, unsigned size) : ViewWorld(world), EntityArray(entityArray), Index(index), Size(size) {}

			unsigned operator*() const
			{
				return EntityArray[Index];
			}

			bool operator==(const Iterator& other) const
			{
				return Index == other.Index || Index == Size;
			}

			bool operator!=(const Iterator& other) const
			{
				return Index != other.Index && Index != Size;
			}

			Iterator& operator++()
			{
				unsigned Entity;
				do {
					Index++;
					Entity = EntityArray[Index];
				} while (!(ViewWorld->Has<ComponentTypes>(Entity) && ...) && Index < Size);
					
				return *this;
			}

			World* ViewWorld = nullptr;
			unsigned* EntityArray = nullptr;
			unsigned Index;
			unsigned Size;
		};

		// View generate first candidate
		const Iterator begin() const
		{
			unsigned index = 0;
			unsigned Entity = EntityArray[index];
			while (!(ViewWorld->Has<ComponentTypes>(Entity) && ...) && index < SmallestCount) 
			{
				index++;
				Entity = EntityArray[index];
			}

			return Iterator(ViewWorld, EntityArray, index, SmallestCount);
		}

		// View generate a sentinel
		const Iterator end() const
		{
			// Give an iterator to the end of this view 
			return Iterator(ViewWorld, EntityArray, SmallestCount, SmallestCount);
		}
	};

}