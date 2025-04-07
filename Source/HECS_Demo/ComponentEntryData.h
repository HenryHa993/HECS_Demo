// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ComponentEntryData.generated.h"

/**
 * 
 */
UCLASS()
class HECS_DEMO_API UComponentEntryData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ComponentLabel;
};
