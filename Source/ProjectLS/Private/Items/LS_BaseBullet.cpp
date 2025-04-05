// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseBullet.h"

ALS_BaseBullet::ALS_BaseBullet()
{

}

void ALS_BaseBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_BaseBullet::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}