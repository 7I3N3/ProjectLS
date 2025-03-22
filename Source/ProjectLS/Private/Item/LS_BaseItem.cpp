// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseItem.h"

ALS_BaseItem::ALS_BaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	bIsUIVisible = false;
}

void ALS_BaseItem::Interact(AActor* Interactor)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interacted with Object!"));
}

void ALS_BaseItem::ShowInteractionUI()
{
	if (!bIsUIVisible)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Interaction Available"));
		bIsUIVisible = true;
	}
}

void ALS_BaseItem::HideInteractionUI()
{
	if (bIsUIVisible)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction Lost"));
		bIsUIVisible = false;
	}
}

void ALS_BaseItem::DisableCollision()
{
	if (ItemMesh)
	{
		ItemMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

void ALS_BaseItem::EnableCollision()
{
	if (ItemMesh)
	{
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMesh->SetCollisionResponseToAllChannels(ECR_Block);
	}
}

void ALS_BaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

