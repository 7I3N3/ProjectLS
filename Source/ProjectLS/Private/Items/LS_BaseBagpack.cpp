// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseBagpack.h"
#include "LS_InventoryComponent.h"
#include "LS_InventoryWidget.h"

ALS_BaseBagpack::ALS_BaseBagpack()
{
	InventoryComponent = CreateDefaultSubobject<ULS_InventoryComponent>(TEXT("InventoryComponent"));
}

void ALS_BaseBagpack::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent->InitializeGrid();
}

void ALS_BaseBagpack::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_BaseBagpack::Equip(ALS_Character* Wearer)
{
	
}

void ALS_BaseBagpack::Unequip(ALS_Character* Wearer)
{
	
}
