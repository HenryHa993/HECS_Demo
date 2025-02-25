// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "GameFramework/Actor.h"
#include "TestEntity.generated.h"

UCLASS()
class HECS_DEMO_API ATestEntity : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Initialise(HECS::World* ecs);

	unsigned EntityID;
};
