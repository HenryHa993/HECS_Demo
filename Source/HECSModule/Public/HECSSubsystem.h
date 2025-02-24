// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HECS.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HECSSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HECSMODULE_API UHECSSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	HECS::World* GetECSWorld() const;

private:
	HECS::World* ECSWorld;
};
