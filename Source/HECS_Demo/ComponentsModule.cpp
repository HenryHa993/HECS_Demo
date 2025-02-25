// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentsModule.h"

void UComponentsModule::Initialise(HECS::World* ecs)
{
	ecs->Register<Test1>();
	ecs->Register<Test2>();
	ecs->Register<Test3>();

	unsigned entity1 = ecs->Entity();
	unsigned entity2 = ecs->Entity();
	unsigned entity3 = ecs->Entity();

	ecs->Add<Test2>(entity1);
	ecs->Add<Test3>(entity3);
	ecs->Add<Test1>(entity2);
	ecs->Add<Test3>(entity1);
}
