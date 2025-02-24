// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECSModuleBase.h"
#include "HECSModule/Public/HECSBootstrap.h"
#include "GameplayBootstrap.generated.h"

UCLASS()
class HECS_DEMO_API AGameplayBootstrap : public AHECSBootstrap
{
	GENERATED_BODY()

protected:
	virtual void Bootstrap(HECS::World* ecs) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UHECSModuleBase>> Modules;
};
