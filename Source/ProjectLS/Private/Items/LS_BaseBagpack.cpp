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

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<ULS_InventoryWidget>(GetWorld(), InventoryWidgetClass);

		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			InventoryWidget->SetInventoryComponent(InventoryComponent);
		}
	}
}

void ALS_BaseBagpack::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_BaseBagpack::Equip(ALS_Character* Wearer)
{
	if (InventoryWidget && Wearer)
	{
		InventoryWidget->SetOwningPlayer(Cast<APlayerController>(Wearer->GetController()));
	}
}

void ALS_BaseBagpack::Unequip(ALS_Character* Wearer)
{
	HideInventoryUI(Cast<APlayerController>(Wearer->GetController()));

	if (InventoryWidget)
	{
		InventoryWidget->SetOwningPlayer(nullptr);
	}
}

void ALS_BaseBagpack::ShowInventoryUI(APlayerController* PC)
{
	if (InventoryWidget && PC)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		PC->bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
	}
}

void ALS_BaseBagpack::HideInventoryUI(APlayerController* PC)
{
	if (InventoryWidget && PC)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}