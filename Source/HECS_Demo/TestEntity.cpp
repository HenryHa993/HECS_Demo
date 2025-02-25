// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEntity.h"

#include "ComponentsModule.h"
#include "HECSSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATestEntity::ATestEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SceneRoot);
	Pointlight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	Pointlight->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ATestEntity::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	Initialise(hecsSubsystem->GetECSWorld());
}

void ATestEntity::Initialise(HECS::World* ecs)
{
	EntityID = ecs->Entity();
	ecs->Add<StaticMeshComponent>(EntityID,{StaticMesh});
	ecs->Add<Light>(EntityID,{Pointlight});
	ecs->Add<CosX>(EntityID,{Radius});
	ecs->Add<SinY>(EntityID,{Radius});
	ecs->Add<LinearZ>(EntityID,{Speed});
}


