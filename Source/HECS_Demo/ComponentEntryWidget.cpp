// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentEntryWidget.h"

#include "ComponentEntryData.h"

void UComponentEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Log, TEXT("Trying to set list item."));
	UComponentEntryData* data = Cast<UComponentEntryData>(ListItemObject);
	if(!data) return;
	UE_LOG(LogTemp, Log, TEXT("List item set."));
	ComponentLabel->SetText(data->ComponentLabel);
}
