// Copyright Epic Games, Inc. All Rights Reserved.

#include "LS_BaseItem.h"
#include "Components/ShapeComponent.h"

ALS_BaseItem::ALS_BaseItem()
{
	
}

void ALS_BaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_BaseItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	if (InteractionOptions.Contains(SelectedOption))
	{
		InteractionOptions[SelectedOption]();
	}
}