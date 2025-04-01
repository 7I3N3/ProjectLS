// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LS_StaticMeshItem.h"
#include "Components/StaticMeshComponent.h"

ALS_StaticMeshItem::ALS_StaticMeshItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ItemMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ALS_StaticMeshItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_StaticMeshItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}