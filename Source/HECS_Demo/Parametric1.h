// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestEntity.h"
#include "Parametric1.generated.h"

UCLASS()
class HECS_DEMO_API AParametric1 : public ATestEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParametric1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Initialise(HECS::World* ecs) override;
};
