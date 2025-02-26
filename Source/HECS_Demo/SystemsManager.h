// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "GameFramework/Actor.h"
#include "SystemsManager.generated.h"

UCLASS()
class HECS_DEMO_API ASystemsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASystemsManager();

public:
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DimSystem(float deltaTime);
	void CosXSystem(float deltaTime);
	void CosYSystem(float deltaTime);
	void CosZSystem(float deltaTime);
	void SinXSystem(float deltaTime);
	void SinYSystem(float deltaTime);
	void SinZSystem(float deltaTime);
	void LinearXSystem(float deltaTime);
	void LinearYSystem(float deltaTime);
	void LinearZSystem(float deltaTime);

private:
	HECS::World* ECS;
};
