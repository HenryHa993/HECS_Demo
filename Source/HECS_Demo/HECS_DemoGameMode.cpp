// Copyright Epic Games, Inc. All Rights Reserved.

#include "HECS_DemoGameMode.h"
#include "HECS_DemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHECS_DemoGameMode::AHECS_DemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
