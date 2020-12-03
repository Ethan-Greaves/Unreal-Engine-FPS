// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealAssignmentGameMode.h"
#include "UnrealAssignmentHUD.h"
#include "UnrealAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealAssignmentGameMode::AUnrealAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealAssignmentHUD::StaticClass();
}
