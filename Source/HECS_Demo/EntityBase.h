// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "EntityBase.generated.h"

UCLASS()
class HECS_DEMO_API AEntityBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntityBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Initialise();

protected:
	HECS::World* ECS;

public:
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	float Radius = 100;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

	UPROPERTY(BlueprintReadOnly)
	int EntityID;
};
