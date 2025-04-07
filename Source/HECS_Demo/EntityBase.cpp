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
	Super::BeginPlay();

	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	ECS = hecsSubsystem->GetECSWorld();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AEntityBase::Initialise);
}

void AEntityBase::Initialise()
{
	EntityID = ECS->Entity();
	UE_LOG(LogTemp, Warning, TEXT("Entity created with ID %u"), EntityID)
	if(ECS == nullptr) return;
	ECS->Add<StaticMeshComponent>(EntityID,{StaticMesh});
	ECS->Add<CosX>(EntityID, {Radius});
	ECS->Add<CosY>(EntityID, {Radius});
}


