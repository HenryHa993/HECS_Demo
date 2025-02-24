#pragma once

namespace HECS
{
	class IDGenerator
	{
		static unsigned int UpdateID()
		{
			static unsigned int value = 0;
			return value++;
		}

	public:
		template<class T>
		static unsigned int GetID()
		{
			static const unsigned int value = UpdateID();
			return value;
		}
	};
	
	class ISparseSet
	{
	};

	template <class T>
	class ComponentPool : ISparseSet
	{
	public:
		std::vector<T> Components;
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
		unsigned int Entity();

		// Add a component to an entity
		//template <class T>
		//void Add(unsigned int entity, T value);

	private:
		unsigned int NumEntities;

		std::vector<std::unique_ptr<ISparseSet>> ComponentPools;
	};

	template <class T>
	void World::Register()
	{
		unsigned int componentId = IDGenerator::GetID<T>();
		ComponentPools[componentId] = std::unique_ptr<ComponentPool<T>>();
		UE_LOG(LogTemp, Warning, TEXT("Component registered with ID %u"), componentId)
	}
}
