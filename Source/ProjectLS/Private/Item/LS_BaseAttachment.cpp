// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseAttachment.h"

ALS_BaseAttachment::ALS_BaseAttachment()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALS_BaseAttachment::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALS_BaseAttachment::AttachToOwner(AActor* OwnerActor)
{
	if (OwnerActor)
	{
		AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}