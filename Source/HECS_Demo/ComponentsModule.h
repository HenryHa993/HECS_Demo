// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECSModuleBase.h"
#include "Components/PointLightComponent.h"
#include "ComponentsModule.generated.h"

/*struct Test0{};
struct Test1{};
struct Test2{};*/
struct Actor
{
	AActor* Value;
};

struct StaticMeshComponent
{
	UStaticMeshComponent* Value;
};

struct Light
{
	UPointLightComponent* Value;
};

struct OscillateLight{};

struct SpinLight{};

struct CosX
{
	float Radius;
};

struct CosY
{
	float Radius;
};

struct CosZ
{
	float Radius;
};

struct SinX
{
	float Radius;
};

struct SinY
{
	float Radius;
};

struct SinZ
{
	float Radius;
};

struct LinearX
{
	float Distance;
};

struct LinearY
{
	float Distance;
};

struct LinearZ
{
	float Distance;
};

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
