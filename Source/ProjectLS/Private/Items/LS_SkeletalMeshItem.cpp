// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LS_SkeletalMeshItem.h"
#include "Components/SkeletalMeshComponent.h"

ALS_SkeletalMeshItem::ALS_SkeletalMeshItem()
{
	SkeletalMesh = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	if (ItemMesh)
	{
		SkeletalMesh->AttachToComponent(ItemMesh, FAttachmentTransformRules::KeepRelativeTransform);

		ItemMesh->SetVisibility(false);
	}

	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMesh->SetSimulatePhysics(false); 
}

void ALS_SkeletalMeshItem::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_SkeletalMeshItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}