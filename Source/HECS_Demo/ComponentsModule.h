// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECSModuleBase.h"
#include "ComponentsModule.generated.h"

struct Test1{};
struct Test2{};
struct Test3{};

/**
 * This class is for component registration
 */
UCLASS()
class HECS_DEMO_API UComponentsModule : public UHECSModuleBase
{
	GENERATED_BODY()

public:
	virtual void Initialise(HECS::World* ecs) override;
};
