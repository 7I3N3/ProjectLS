// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseMag.h"

ALS_BaseMag::ALS_BaseMag()
{

}

void ALS_BaseMag::BeginPlay()
{
	Super::BeginPlay();
}

void ALS_BaseMag::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

TSubclassOf<ALS_BaseBullet> ALS_BaseMag::ConsumeBullet()
{
	if (IsEmpty()) return TSubclassOf<ALS_BaseBullet>();

	return AmmoStack.Pop();
}

bool ALS_BaseMag::LoadAmmo(TSubclassOf<ALS_BaseBullet> Bullet)
{
	if (IsFull()) return false;
	if (!AvailableBulletClasses.Contains(Bullet)) return false;

	AmmoStack.Push(Bullet);
	return true;
}

void ALS_BaseMag::OnAttached(AActor* Parent, FName SocketName)
{
	if (Parent)
	{
		AttachToActor(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}

	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ALS_BaseMag::OnDetached()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}