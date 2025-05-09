// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "GameFramework/Actor.h"
#include "HECSBootstrap.generated.h"

UCLASS()
class HECSMODULE_API AHECSBootstrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHECSBootstrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Bootstrap(HECS::World* ecs);
};
