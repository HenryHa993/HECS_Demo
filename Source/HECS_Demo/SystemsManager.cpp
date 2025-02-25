// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemsManager.h"

#include "ComponentsModule.h"
#include "HECSSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASystemsManager::ASystemsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASystemsManager::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	ECS = hecsSubsystem->GetECSWorld();

	Super::BeginPlay();
}

// Called every frame
void ASystemsManager::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Running System"))
	TestSystem(ECS, DeltaTime);

	Super::Tick(DeltaTime);
}

void ASystemsManager::TestSystem(HECS::World* ecs, float deltaTime)
{
	Actor* actorArray= ecs->GetAll<Actor>();
	
	/*for(Actor actorType : actorArray)
	{
		auto* actor = actorType.Value;
		FVector newLocation = actor->GetActorLocation();
		newLocation.Z += deltaTime * 100;
		actor->SetActorLocation(newLocation);
	}*/
	UE_LOG(LogTemp, Warning, TEXT("Running System"))

	AActor* actor = actorArray[0].Value;
	FVector newLocation = actor->GetActorLocation();
	newLocation.Z += deltaTime * 100;
	actor->SetActorLocation(newLocation);
}

