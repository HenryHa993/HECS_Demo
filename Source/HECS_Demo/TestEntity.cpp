// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEntity.h"

#include "ComponentsModule.h"
#include "HECSSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATestEntity::ATestEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	ecs->Add<Actor>(EntityID,{this});
}


