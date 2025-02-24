// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentsModule.h"

void UComponentsModule::Initialise(HECS::World* ecs)
{
	ecs->Register<Transform>();
	ecs->Register<TestStruct1>();
	ecs->Register<TestStruct2>();
}
