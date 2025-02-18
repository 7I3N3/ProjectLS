// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_GameMode.h"

ALS_GameMode::ALS_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ProjectLS/Blueprints/BP_LS_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}