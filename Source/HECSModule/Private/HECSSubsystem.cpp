// Fill out your copyright notice in the Description page of Project Settings.


#include "HECSSubsystem.h"

void UHECSSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ECSWorld = new HECS::World();
	
	Super::Initialize(Collection);
}

void UHECSSubsystem::Deinitialize()
{
	if(ECSWorld)
	{
		delete ECSWorld;
	}
	Super::Deinitialize();
}

HECS::World* UHECSSubsystem::GetECSWorld() const
{
	return ECSWorld;
}
