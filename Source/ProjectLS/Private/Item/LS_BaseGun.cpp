// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseGun.h"
#include "LS_BaseBullet.h"
#include "LS_BaseMag.h"
#include "Kismet/GameplayStatics.h"

ALS_BaseGun::ALS_BaseGun()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultMuzzleLocation"));
	DefaultMuzzleLocation->SetupAttachment(RootComponent);
	DefaultMuzzleLocation->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
}

void ALS_BaseGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALS_BaseGun::AddAttachment(ALS_GunAttachment* Attachment)
{
	if (!Attachment)
	{
		return;
	}

	FName SlotName = Attachment->GetSlotName();

	if (Attachments.Contains(SlotName))
	{
		RemoveAttachment(SlotName);
	}
	Attachments.Add(SlotName, Attachment);

	Attachment->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ALS_BaseGun::RemoveAttachment(FName AttachmentSlot)
{
	if (ALS_GunAttachment* const* FoundAttachment = Attachments.Find(AttachmentSlot))
	{
		(*FoundAttachment)->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Attachments.Remove(AttachmentSlot);
	}
}

bool ALS_BaseGun::Fire()
{
	ALS_GunAttachment* Attachment = GetAttachment("Mag");
	if (!Attachment)
	{
		return false;
	}

	ALS_BaseMag* Mag = Cast<ALS_BaseMag>(Attachment);
	if (!Mag)
	{
		return false;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	TSubclassOf<ALS_BaseBullet> BulletClass = Mag->ConsumeBullet();
	if (!BulletClass)
	{
		return false;
	}

	FTransform MuzzleTransform = GetMuzzleTransform();
	FVector SpawnLocation = MuzzleTransform.GetLocation();
	FRotator SpawnRotation = MuzzleTransform.GetRotation().Rotator();

	ALS_BaseBullet* Bullet = World->SpawnActor<ALS_BaseBullet>(BulletClass, SpawnLocation, SpawnRotation);
	if (!Bullet)
	{
		return false;
	}

	Bullet->FireInDirection(SpawnRotation.Vector());

	return true;
}

ALS_GunAttachment* ALS_BaseGun::GetAttachment(FName AttachmentSlot) const
{
	if (ALS_GunAttachment* const* FoundAttachment = Attachments.Find(AttachmentSlot))
	{
		return *FoundAttachment;
	}
	return nullptr;
}

FTransform ALS_BaseGun::GetMuzzleTransform() const
{
	ALS_GunAttachment* Attachment = GetAttachment("Muzzle");
	if (!Attachment)
	{
		return DefaultMuzzleLocation->GetComponentTransform();
	}

	/*
	ALS_BaseMuzzle* Muzzle = Cast<ALS_BaseMuzzle>(Attachment);
	if (!Muzzle)
	{
		return DefaultMuzzleLocation->GetComponentTransform();
	}
	*/

	return Attachment->GetActorTransform();
}