// Fill out your copyright notice in the Description page of Project Settings.


#include "Parametric1.h"

#include "ComponentsModule.h"


// Sets default values
AParametric1::AParametric1() : ATestEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AParametric1::BeginPlay()
{
	Super::BeginPlay();
	
}

void AParametric1::Initialise(HECS::World* ecs)
{
	EntityID = ecs->Entity();
	ecs->Add<StaticMeshComponent>(EntityID,{StaticMesh});
	ecs->Add<Light>(EntityID,{Pointlight});
	ecs->Add<CosY>(EntityID,{Radius});
	ecs->Add<SinZ>(EntityID,{Radius});
}
