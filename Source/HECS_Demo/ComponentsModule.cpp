// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentsModule.h"

void UComponentsModule::Initialise(HECS::World* ecs)
{
	ecs->Register<Actor>();
	ecs->Register<StaticMeshComponent>();
	ecs->Register<Light>();
	ecs->Register<OscillateLight>();
	ecs->Register<SpinLight>();
	ecs->Register<CosX>();
	ecs->Register<CosY>();
	ecs->Register<CosZ>();
	ecs->Register<SinX>();
	ecs->Register<SinY>();
	ecs->Register<SinZ>();
	ecs->Register<LinearX>();
	ecs->Register<LinearY>();
	ecs->Register<LinearZ>();
}
