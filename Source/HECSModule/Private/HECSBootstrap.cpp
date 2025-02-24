// Fill out your copyright notice in the Description page of Project Settings.


#include "HECSBootstrap.h"

#include "HECSSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHECSBootstrap::AHECSBootstrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AHECSBootstrap::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	HECS::World* ecs = hecsSubsystem->GetECSWorld();
	Bootstrap(ecs);
	
	Super::BeginPlay();
}

void AHECSBootstrap::Bootstrap(HECS::World* ecs)
{
}


