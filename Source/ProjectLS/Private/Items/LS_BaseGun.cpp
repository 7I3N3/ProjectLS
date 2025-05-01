// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseGun.h"
#include "LS_BaseMag.h"
#include "LS_Character.h"
#include "LS_PlayerStatusWidget.h"

ALS_BaseGun::ALS_BaseGun()
{

}

void ALS_BaseGun::BeginPlay()
{
	Super::BeginPlay();

	if (ItemMesh)
	{
		ItemMesh->SetSimulatePhysics(true);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	InteractionOptions.Add(TEXT("Take"), [this](ALS_Character* Interactor) { ALS_BaseGun::Take(Interactor); });
	InteractionOptions.Add(TEXT("Equip"), [this](ALS_Character* Interactor) { ALS_BaseGun::Equip(Interactor); });
	InteractionOptions.Add(TEXT("Examine"), [this](ALS_Character* Interactor) { ALS_BaseGun::Examine(Interactor); });
}

void ALS_BaseGun::Take(ALS_Character* Interactor)
{
	if (!Interactor) return;

	if (Interactor->TakeItem(this))
	{
		UE_LOG(LogTemp, Log, TEXT("Success Take Item"));
		if (ItemMesh)
		{
			SkeletalMesh->SetVisibility(false);
			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ALS_BaseGun::Examine(ALS_Character* Interactor)
{

}

void ALS_BaseGun::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

bool ALS_BaseGun::AttachAttachment(TScriptInterface<ILS_Attachable> NewAttachment, FName SlotName)
{
	if (!NewAttachment) return false;

	EAttachmentSlotType SlotType = NewAttachment->GetAttachmentSlotType();

	// ∫Û ΩΩ∑‘¿Ã ¿÷¿∏∏È
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && !Slot.Attachment)
		{
			Slot.Attachment = NewAttachment; 

			NewAttachment->OnAttached(this, Slot.SlotName);

			return true;
		}
	}

	//∫Û ΩΩ∑‘¿Ã æ¯¿∏∏È SlotNameø° ∏¬∞‘ ±≥√º
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && Slot.SlotName == SlotName)
		{
			DetachAttachment(SlotType, SlotName);

			Slot.Attachment = NewAttachment;

			NewAttachment->OnAttached(this, Slot.SlotName);

			return true;
		}
	}

	return false;
}

bool ALS_BaseGun::DetachAttachment(EAttachmentSlotType SlotType, FName SlotName)
{
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && Slot.SlotName == SlotName)
		{
			if (Slot.Attachment)
			{
				Slot.Attachment->OnDetached();

				Slot.Attachment = nullptr;
				return true;
			}
		}
	}

	return false;
}

void ALS_BaseGun::Equip(ALS_Character* Wearer)
{
	if (!Wearer) return;
	
	Wearer->EquipItem(this);

	if (ItemMesh)
	{
		ItemMesh->SetSimulatePhysics(false);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(Wearer->GetMesh(), Rules, TEXT("hand_r_ik"));

	bIsEquipped = true;
	EquippedCharacter = Wearer;
}
void ALS_BaseGun::Unequip(ALS_Character* Wearer)
{
	if (!bIsEquipped || !Wearer) return;

	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (ItemMesh)
	{
		ItemMesh->SetSimulatePhysics(true);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	bIsEquipped = false;
	EquippedCharacter = nullptr;
}

void ALS_BaseGun::StartFiring()
{
	switch (CurrentFireMode)
	{
	case EFireMode::SemiAuto:
		FireBullet();
		break;

	case EFireMode::Burst:
		BurstShotsFired = 0;
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ALS_BaseGun::HandleBurstFire, FireRate, true);
		break;

	case EFireMode::FullAuto:
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ALS_BaseGun::FireBullet, FireRate, true);
		break;
	}
}

void ALS_BaseGun::StopFiring()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	BurstShotsFired = 0;
}

void ALS_BaseGun::FireBullet()
{
	// ≈∫√¢ »Æ¿Œ
	auto MagInterface = GetAttachment(EAttachmentSlotType::AS_Mag);
	ALS_BaseMag* Mag = Cast<ALS_BaseMag>(MagInterface.GetObject());
	if (!Mag || Mag->IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No mag or empty."));
		StopFiring();
		return;
	}

	auto BulletClass = Mag->ConsumeBullet();
	if (!BulletClass) return;

	FActorSpawnParameters Params;
	auto SpawnLoc = GetMuzzleLocation();
	auto SpawnRot = GetMuzzleRotation();

	GetWorld()->SpawnActor<ALS_BaseBullet>(BulletClass, SpawnLoc, SpawnRot, Params);
}

void ALS_BaseGun::HandleBurstFire()
{
	if (BurstShotsFired >= BurstCount)
	{
		StopFiring();
		return;
	}

	FireBullet();
	BurstShotsFired++;
}

void ALS_BaseGun::SwitchFireMode()
{
	EFireMode NextMode = CurrentFireMode;

	do
	{
		switch (NextMode)
		{
		case EFireMode::SemiAuto: NextMode = EFireMode::Burst; break;
		case EFireMode::Burst:    NextMode = EFireMode::FullAuto; break;
		case EFireMode::FullAuto: NextMode = EFireMode::SemiAuto; break;
		default:                  NextMode = EFireMode::SemiAuto; break;
		}
	} while (!EnumHasAnyFlags(SupportedFireModes, NextMode));

	CurrentFireMode = NextMode;

	UE_LOG(LogTemp, Log, TEXT("Fire Mode: %d"), (uint8)CurrentFireMode);
}

TScriptInterface<ILS_Attachable> ALS_BaseGun::GetAttachment(EAttachmentSlotType SlotType, FName SlotName) const
{
	for (const FAttachmentSlot& Slot : Attachments)
	{
		if (SlotName.IsNone())
		{
			if (Slot.SlotType == SlotType && Slot.Attachment)
			{
				return Slot.Attachment;
			}
		}
		else
		{
			if (Slot.SlotType == SlotType && Slot.SlotName == SlotName && Slot.Attachment)
			{
				return Slot.Attachment;
			}
		}
	}

	return nullptr;
}

FVector ALS_BaseGun::GetMuzzleLocation() const
{
	if (const TScriptInterface<ILS_Attachable> MuzzleAttachment = GetAttachment(EAttachmentSlotType::AS_Muzzle))
	{
		if (const AActor* MuzzleActor = Cast<AActor>(MuzzleAttachment.GetObject()))
		{
			return MuzzleActor->GetActorLocation();
		}
	}

	const USkeletalMeshComponent* MeshComp = FindComponentByClass<USkeletalMeshComponent>();
	if (MeshComp && MeshComp->DoesSocketExist("Muzzle"))
	{
		return MeshComp->GetSocketLocation("Muzzle");
	}

	return GetActorLocation();
}

FRotator ALS_BaseGun::GetMuzzleRotation() const
{
	if (const TScriptInterface<ILS_Attachable> MuzzleAttachment = GetAttachment(EAttachmentSlotType::AS_Muzzle))
	{
		if (const AActor* MuzzleActor = Cast<AActor>(MuzzleAttachment.GetObject()))
		{
			return MuzzleActor->GetActorRotation();
		}
	}

	const USkeletalMeshComponent* MeshComp = FindComponentByClass<USkeletalMeshComponent>();
	if (MeshComp && MeshComp->DoesSocketExist("Muzzle"))
	{
		return MeshComp->GetSocketRotation("Muzzle");
	}

	return GetActorRotation();
}