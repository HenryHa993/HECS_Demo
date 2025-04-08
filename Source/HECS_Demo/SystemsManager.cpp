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
	CosXSystem(DeltaTime);
	CosYSystem(DeltaTime);
	CosZSystem(DeltaTime);
	SinXSystem(DeltaTime);
	SinYSystem(DeltaTime);
	SinZSystem(DeltaTime);
	LinearXSystem(DeltaTime);
	LinearYSystem(DeltaTime);
	LinearZSystem(DeltaTime);
	Super::Tick(DeltaTime);
}

void ASystemsManager::CosXSystem(float deltaTime)
{
    for (unsigned entity : HECS::View<StaticMeshComponent, CosX>(ECS))
    {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        CosX& cosXType = ECS->Get<CosX>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = cosXType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.X = radius * FMath::Cos(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::CosYSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, CosY>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        CosY& cosYType = ECS->Get<CosY>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = cosYType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.Y = radius * FMath::Cos(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::CosZSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, CosZ>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        CosZ& cosZType = ECS->Get<CosZ>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = cosZType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.Z = radius * FMath::Cos(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::SinXSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, SinX>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        SinX& sinXType = ECS->Get<SinX>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = sinXType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.X = radius * FMath::Sin(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::SinYSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, SinY>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        SinY& sinYType = ECS->Get<SinY>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = sinYType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.Y = radius * FMath::Sin(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::SinZSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, SinZ>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        SinZ& sinZType = ECS->Get<SinZ>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float radius = sinZType.Radius;

        FVector newLocation = mesh->GetRelativeLocation();
        newLocation.Z = radius * FMath::Sin(GetWorld()->GetTimeSeconds());

        mesh->SetRelativeLocation(newLocation);
    }
}

void ASystemsManager::LinearXSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, LinearX>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        LinearX& xType = ECS->Get<LinearX>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float distance = xType.Distance;

        mesh->AddRelativeRotation(FRotator(0, 0, deltaTime * distance));
    }
}

// Pitch rotations have an issue with it.
void ASystemsManager::LinearYSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, LinearY>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        LinearY& yType = ECS->Get<LinearY>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float distance = yType.Distance;

        if(mesh->GetRelativeRotation().Pitch > 87)
        {
            mesh->AddRelativeRotation(FRotator(0, -87, 0));
            return;
        }
        mesh->AddRelativeRotation(FRotator(deltaTime * distance, 0, 0));
    }
}

void ASystemsManager::LinearZSystem(float deltaTime) {
    for (unsigned entity : HECS::View<StaticMeshComponent, LinearZ>(ECS)) {
        StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
        LinearZ& zType = ECS->Get<LinearZ>(entity);

        UStaticMeshComponent* mesh = meshType.Value;
        float distance = zType.Distance;

        mesh->AddRelativeRotation(FRotator(0, deltaTime * distance, 0));

    }
}
