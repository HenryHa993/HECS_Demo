// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "EntityInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class HECS_DEMO_API UEntityInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UListView> ComponentList;
};
