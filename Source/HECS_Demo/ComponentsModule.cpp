// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentsModule.h"

void UComponentsModule::Initialise(HECS::World* ecs)
{
	/*ecs->Register<Test0>();
	ecs->Register<Test1>();
	ecs->Register<Test2>();

	unsigned entity0 = ecs->Entity();
	unsigned entity1 = ecs->Entity();
	unsigned entity2 = ecs->Entity();

	ecs->Add<Test1>(entity0); // 0 1
	
	ecs->Has<Test1>(entity0); // 1
	ecs->Has<Test0>(entity0); // 0
	
	ecs->Add<Test0>(entity0); // 0 1
	
	ecs->Has<Test0>(entity0); // 1
	
	ecs->Add<Test2>(entity2); // 2 2
	ecs->Add<Test0>(entity1); // 0 1
	ecs->Add<Test2>(entity0); // 2 0
	ecs->Add<Test1>(entity1); // 0 1
	ecs->Add<Test1>(entity2); // 0 1*/

	ecs->Register<Actor>();
}
