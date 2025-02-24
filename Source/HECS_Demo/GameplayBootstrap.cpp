// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayBootstrap.h"

void AGameplayBootstrap::Bootstrap(HECS::World* ecs)
{
	for(auto moduleType : Modules)
	{
		auto module = NewObject<UHECSModuleBase>(this, moduleType); // Creating UObjects at runtime, the bootstrap is the owner
		module->Initialise(ecs);
	}}
