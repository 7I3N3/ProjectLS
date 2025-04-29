// Copyright Epic Games, Inc. All Rights Reserved.

#include "LS_BaseItem.h"
#include "Components/StaticMeshComponent.h"

ALS_BaseItem::ALS_BaseItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ItemMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(true);
	ItemMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
}

void ALS_BaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_BaseItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	if (InteractionOptions.Contains(SelectedOption))
	{
		ALS_Character* Interactor = Cast<ALS_Character>(PlayerController->GetPawn());

		if (Interactor)
		{
			InteractionOptions[SelectedOption](Interactor);
		}
	}
}

void ALS_BaseItem::AddStack(int32 Amount)
{
	CurrentStackCount = FMath::Min(MaxStackCount, CurrentStackCount + Amount);
}