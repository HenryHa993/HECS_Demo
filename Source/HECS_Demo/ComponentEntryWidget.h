// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ComponentEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class HECS_DEMO_API UComponentEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> ComponentLabel;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
