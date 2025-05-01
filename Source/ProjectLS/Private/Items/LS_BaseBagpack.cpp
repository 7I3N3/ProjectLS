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

	InventoryComponent->InitializeInventory();

	InteractionOptions.Add(TEXT("Equip"), [this](ALS_Character* Interactor) { ALS_BaseBagpack::Equip(Interactor); });
}

void ALS_BaseBagpack::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_BaseBagpack::Equip(ALS_Character* Wearer)
{
	if (!Wearer) return;

	Wearer->EquipItem(this);

	EquippedCharacter = Wearer;

	if (ItemMesh)
	{
		ItemMesh->SetSimulatePhysics(false);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ALS_BaseBagpack::Unequip(ALS_Character* Wearer)
{
	EquippedCharacter = nullptr;

	if (ItemMesh)
	{
		ItemMesh->SetSimulatePhysics(true);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
