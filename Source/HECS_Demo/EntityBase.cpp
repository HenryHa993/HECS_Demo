// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"

#include "ComponentsModule.h"
#include "HECSSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEntityBase::AEntityBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AEntityBase::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	Initialise(hecsSubsystem->GetECSWorld());
}

void AEntityBase::Initialise(HECS::World* ecs)
{
	EntityID = ecs->Entity();
	UE_LOG(LogTemp, Warning, TEXT("Entity created with ID %u"), EntityID)
	ecs->Add<StaticMeshComponent>(EntityID,{StaticMesh});
}


