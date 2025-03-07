// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseItem.h"

ALS_BaseItem::ALS_BaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALS_BaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

