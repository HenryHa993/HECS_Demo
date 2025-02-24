#pragma once

#define MAX_ENTITIES 1000

namespace HECS
{
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

	/*struct Index
	{
		unsigned Entity;
		unsigned ComponentIndex;
		unsigned Next;
	};*/

	template <class T>
	struct ComponentIndex
	{
		unsigned Entity;
		T Component;
	};
	
	class ISparseSet{};

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

		bool Has(unsigned entity)
		{
			return
				SparseArray[entity] != UINT_MAX
				&&
				PackedArray[SparseArray[entity]].Entity == entity;
		}

		T& Lookup(unsigned entity)
		{
			return PackedArray[SparseArray[entity]].Component;
		}

		void Add(unsigned entity, T value)
		{
			SparseArray[entity] = NumComponents++;
			PackedArray[SparseArray[entity]].Entity = entity;
			PackedArray[SparseArray[entity]].Component = value;
		}

		void Remove(unsigned entity)
		{
			unsigned index = SparseArray[entity];
			
			ComponentIndex<T>& componentIndex = PackedArray[index];
			componentIndex = PackedArray[--NumComponents];
			
			SparseArray[componentIndex.Entity] = index;
			SparseArray[entity] = UINT_MAX;
		}
		
		unsigned NumComponents;
		
		unsigned SparseArray[MAX_ENTITIES];
		ComponentIndex<T> PackedArray[MAX_ENTITIES];
	};
	
	// Manages entities, components and systems
	class World
	{
	public:
		World() = default;

		// Register a component to the system
		template <class T>
		void Register();

		// Create a new entity, return it's ID
		unsigned Entity();

		// Add a component to an entity
		//template <class T>
		//void Add(unsigned int entity, T value);

	private:
		unsigned NumEntities;

		std::vector<std::unique_ptr<ISparseSet>> ComponentPools;
	};

	template <class T>
	void World::Register()
	{
		unsigned componentId = IDGenerator::GetID<T>();
		//ComponentPools.resize(componentId + 1);
		//ComponentPools[componentId] = std::make_unique<ComponentPool<T>>();
		ComponentPools.push_back(std::make_unique<ComponentPool<T>>());
		UE_LOG(LogTemp, Warning, TEXT("Component registered with ID %u"), componentId)
	}
}
