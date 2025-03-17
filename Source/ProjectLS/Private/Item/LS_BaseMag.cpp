// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseMag.h"
#include "LS_BaseBullet.h"

ALS_BaseMag::ALS_BaseMag()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALS_BaseMag::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseMag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<ALS_BaseBullet> ALS_BaseMag::ConsumeBullet()
{
	if (IsEmpty())
	{
		return nullptr;
	}

	TSubclassOf<ALS_BaseBullet> Bullet = AmmoStack.Pop();
	return Bullet;
}

bool ALS_BaseMag::LoadMag(TSubclassOf<ALS_BaseBullet> Bullet)
{
	if (IsFull())
	{
		return false;
	}

	AmmoStack.Push(Bullet);
	return true;
}
