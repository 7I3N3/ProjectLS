// Copyright Epic Games, Inc. All Rights Reserved.

#include "LS_GameMode.h"
#include "LS_Character.h"
#include "UObject/ConstructorHelpers.h"

ALS_GameMode::ALS_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ProjectLS/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
