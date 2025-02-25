#pragma once

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
	 * Wrapper around component to confirm component owner
	 */
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
		void Register()
		{
			unsigned componentId = IDGenerator::GetID<T>();
			ComponentPools.push_back(std::make_unique<ComponentPool<T>>());
			
			UE_LOG(LogTemp, Warning, TEXT("Component registered with ID %u"), componentId)
		}

		template <class T>
		void Add(unsigned entity, T value = T())
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding Component %u to Entity %u"), IDGenerator::GetID<T>(), entity)
			
			ComponentPool<T>* componentPool = static_cast<ComponentPool<T>*>(ComponentPools[IDGenerator::GetID<T>()].get());
			componentPool->Add(entity, value);
		}

		// Create a new entity, return it's ID
		unsigned Entity()
		{
			UE_LOG(LogTemp, Warning, TEXT("Entity created with ID %u"), NumEntities)

			return NumEntities++;
		}

	private:
		unsigned NumEntities;

		std::vector<std::unique_ptr<ISparseSet>> ComponentPools;
	};

}
