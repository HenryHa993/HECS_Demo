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
	/*DimSystem(DeltaTime);
	CosXSystem(DeltaTime);
	CosYSystem(DeltaTime);
	CosZSystem(DeltaTime);
	SinXSystem(DeltaTime);
	SinYSystem(DeltaTime);
	SinZSystem(DeltaTime);
	LinearXSystem(DeltaTime);
	LinearYSystem(DeltaTime);
	LinearZSystem(DeltaTime);*/
	Super::Tick(DeltaTime);
}

void ASystemsManager::DimSystem(float deltaTime)
{
	for(unsigned entity = 0; entity < ECS->GetNumEntities(); entity++)
	{
		if(!ECS->Has<Light>(entity) || !ECS->Has<Dim>(entity))
		{
			continue;
		}

		Light& lightType = ECS->Get<Light>(entity);
		
		UPointLightComponent* light = lightType.Value;
		UE_LOG(LogTemp, Warning, TEXT("DIMMING %f"), light->Intensity)

		light->SetIntensity(light->Intensity - deltaTime * 100.0f);
	}
}

void ASystemsManager::CosXSystem(float deltaTime)
{
	for(unsigned entity = 0; entity < ECS->GetNumEntities(); entity++)
	{
		if(!ECS->Has<CosX>(entity) || !ECS->Has<StaticMeshComponent>(entity))
		{
			continue;
		}

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
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<CosY>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

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
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<CosZ>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

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
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<SinX>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

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
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<SinY>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

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
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<SinZ>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

		StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
		SinZ& sinZType = ECS->Get<SinZ>(entity);

		UStaticMeshComponent* mesh = meshType.Value;
		float radius = sinZType.Radius;

		FVector newLocation = mesh->GetRelativeLocation();
		newLocation.Z = radius * FMath::Sin(GetWorld()->GetTimeSeconds());

		mesh->SetRelativeLocation(newLocation);
	}
}

void ASystemsManager::LinearXSystem(float deltaTime)
{
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<LinearX>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

		StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
		LinearX& xType = ECS->Get<LinearX>(entity);

		UStaticMeshComponent* mesh = meshType.Value;
		float distance = xType.Distance;

		float sinValue = FMath::Sin(GetWorld()->GetTimeSeconds());
		float x = sinValue * distance;

		FVector newLocation = mesh->GetRelativeLocation();
		newLocation.X = x;
		mesh->SetRelativeLocation(newLocation);
	}
}

void ASystemsManager::LinearYSystem(float deltaTime)
{
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<LinearY>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

		StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
		LinearY& yType = ECS->Get<LinearY>(entity);

		UStaticMeshComponent* mesh = meshType.Value;
		float distance = yType.Distance;

		float sinValue = FMath::Sin(GetWorld()->GetTimeSeconds());
		float y = sinValue * distance;

		FVector newLocation = mesh->GetRelativeLocation();
		newLocation.Y = y;
		mesh->SetRelativeLocation(newLocation);
	}
}

void ASystemsManager::LinearZSystem(float deltaTime)
{
	for (unsigned entity = 0; entity < ECS->GetNumEntities(); entity++) {
		if (!ECS->Has<LinearZ>(entity) || !ECS->Has<StaticMeshComponent>(entity)) {
			continue;
		}

		StaticMeshComponent& meshType = ECS->Get<StaticMeshComponent>(entity);
		LinearZ& zType = ECS->Get<LinearZ>(entity);

		UStaticMeshComponent* mesh = meshType.Value;
		float distance = zType.Distance;

		float sinValue = FMath::Sin(GetWorld()->GetTimeSeconds());
		float z = sinValue * distance;

		FVector newLocation = mesh->GetRelativeLocation();
		newLocation.Z = z;
		mesh->SetRelativeLocation(newLocation);
	}
}
