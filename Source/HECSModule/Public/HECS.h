#pragma once

#include <sstream>

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
	
	class ISparseSet
	{
	public:
		virtual bool Has(unsigned entity) = 0;
	};

	template <class T>
	class ComponentPool : public ISparseSet
	{
	public:
		ComponentPool() : NumComponents(0)
		{
			for(unsigned i = 0; i < MAX_ENTITIES; i++)
			{
				SparseArray[i] = UINT_MAX;
			}
		};
		
		bool Has(unsigned entity) override
		{
			return
				SparseArray[entity] != UINT_MAX
				&&
				EntityPackedArray[SparseArray[entity]] == entity;
		}

		T& Lookup(unsigned entity)
		{
			return ComponentPackedArray[SparseArray[entity]];
		}

		void Add(unsigned entity, T value)
		{
			/*if(Has(entity))
			{
				return;
			}*/
			
			SparseArray[entity] = NumComponents++;
			EntityPackedArray[SparseArray[entity]] = entity;
			ComponentPackedArray[SparseArray[entity]] = value;

			FString entityStr(EntityArrayToString().c_str());
			UE_LOG(LogTemp, Warning, TEXT("Entities in Component Pool %u : %s"), IDGenerator::GetID<T>(), *entityStr)
		}

		T* GetComponents()
		{
			return ComponentPackedArray;
		}

		void Remove(unsigned entity)
		{
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
			for(unsigned i = 0; i < NumComponents; i++)
			{
				string << EntityPackedArray[i] << " ";
			}
			string << "]";
			return string.str();
		}
		
		unsigned NumComponents;
		
		unsigned SparseArray[MAX_ENTITIES];
		unsigned EntityPackedArray[MAX_ENTITIES];
		T ComponentPackedArray[MAX_ENTITIES];
		
	};
	
	// Manages entities, components and systems
	class World
	{
	public:
		World() = default;

		// Register a component to the system
		template <class T>
		void Register()
		{
			unsigned componentId = IDGenerator::GetID<T>();
			ComponentPools.push_back(std::make_unique<ComponentPool<T>>());
			
			UE_LOG(LogTemp, Warning, TEXT("Component registered with ID %u"), componentId)
		}

		template <class T>
		bool Has(unsigned entity)
		{
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			bool hasComponent = componentPool->Has(entity);

			//UE_LOG(LogTemp, Warning, TEXT("Component Pool %u has Entity %u : %u"),IDGenerator::GetID<T>(),entity, hasComponent)
			
			return hasComponent;
		}

		template <class T>
		void Add(unsigned entity, T value = T())
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding Component %u to Entity %u"), IDGenerator::GetID<T>(), entity)
			
			ComponentPool<T>* componentPool = GetComponentPool<T>();
			componentPool->Add(entity, value);
		}

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
			//UE_LOG(LogTemp, Warning, TEXT("Entity created with ID %u"), NumEntities)

			return NumEntities++;
		}

		unsigned GetNumEntities() const
		{
			return NumEntities;
		}
		
		template <class T>
		ComponentPool<T>* GetComponentPool()
		{
			ComponentPool<T>* componentPool = static_cast<ComponentPool<T>*>(ComponentPools[IDGenerator::GetID<T>()].get());
			return componentPool;
		}

	private:
		unsigned NumEntities;

		std::vector<std::unique_ptr<ISparseSet>> ComponentPools;
	};

	/*
	 * Scene view lets you filter out by entities which actually have the
	 * components you are interested in.
	 */
	/*template <class ...Ts>
	class SceneView
	{
	public:
		// Fill component pools list based on type arguments
		SceneView(World* ecs) : ECS(ecs)
		{}
		
		World* ECS = nullptr;

		struct Iterator
		{
			Iterator(World* ecs, unsigned entity)
				: ECS(ecs), Entity(entity)
			{
				(AddComponentPool<Ts>(),...);
			}

			template <class T>
			void AddComponentPool()
			{
				ViewPools[NumPools++] = ECS->GetComponentPool<T>();
			}

			unsigned operator*() const
			{
				// give back the entityID we're currently at
				return Entity;
			}
	
			bool operator==(const Iterator& other) const
			{
				return Entity == other.Entity;
			}

			bool operator!=(const Iterator& other) const
			{
				return Entity != other.Entity;
			}

			Iterator& operator++()
			{
				for(; Entity < ECS->GetNumEntities(); Entity++)
				{
					if(IsEntityValid(Entity))
					{
						return *this;
					}
				}
				return *this;
			}

			bool IsEntityValid(unsigned entity)
			{
				for(unsigned i = 0; i < NumPools; i++)
				{
					if(!ViewPools[i]->Has(entity))
					{
						return false;
					}
				}
				return true;
			}

			World* ECS;
			ISparseSet* ViewPools[sizeof...(Ts)];

			unsigned Entity;
			unsigned NumPools;
		};

		const Iterator begin() const
		{
			return ++Iterator(ECS, 0);
		}

		const Iterator end() const
		{
			return Iterator(ECS, 1);
		}
	};*/
}
