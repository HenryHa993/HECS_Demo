// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "UObject/Object.h"
#include "HECSModuleBase.generated.h"

/**
 * 
 */
UCLASS()
class HECSMODULE_API UHECSModuleBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialise(HECS::World* ecs);
};
