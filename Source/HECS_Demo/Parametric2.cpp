// Fill out your copyright notice in the Description page of Project Settings.


#include "Parametric2.h"

#include "ComponentsModule.h"


// Sets default values
AParametric2::AParametric2() : ATestEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AParametric2::BeginPlay()
{
	Super::BeginPlay();
	
}

void AParametric2::Initialise(HECS::World* ecs)
{
	EntityID = ecs->Entity();
	UE_LOG(LogTemp, Warning, TEXT("Entity created with ID %u"), EntityID)
	ecs->Add<StaticMeshComponent>(EntityID,{StaticMesh});
	ecs->Add<Light>(EntityID,{Pointlight});
	ecs->Add<LinearY>(EntityID,{Speed});
	ecs->Add<LinearZ>(EntityID,{Speed});
}

