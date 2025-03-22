// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputConfigComponent.h"
#include "InputModule/Private/MoveInputComponent.h"
#include "InputModule/Private/LookInputComponent.h"
#include "InputModule/Private/JumpInputComponent.h"
#include "InputModule/Private/InteractInputComponent.h"
#include "InputModule/Private/PrimaryAttackInputComponent.h"
#include "InputModule/Private/AlternativeAttackInputComponent.h"
#include "LS_BaseItem.h"
#include "LS_Interactable.h"
#include "AbilitySystemComponent.h"
#include "LS_GA_EquipAbility.h"
#include "LS_EnumUtils.h"

ALS_Character::ALS_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), FName("head"));
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	InputConfig = CreateDefaultSubobject<UInputConfigComponent>(TEXT("InputConfig"));

	MoveInput = CreateDefaultSubobject<UMoveInputComponent>(TEXT("MoveInput"));
	LookInput = CreateDefaultSubobject<ULookInputComponent>(TEXT("LookInput"));
	JumpInput = CreateDefaultSubobject<UJumpInputComponent>(TEXT("JumpInput"));
	InteractInput = CreateDefaultSubobject<UInteractInputComponent>(TEXT("InteractInput"));
	PrimaryAttackInput = CreateDefaultSubobject<UPrimaryAttackInputComponent>(TEXT("PrimaryAttackInput"));
	AlternativeAttackInput = CreateDefaultSubobject<UAlternativeAttackInputComponent>(TEXT("AlternativeAttackInput"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ALS_Character::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentInteract = nullptr;
}

void ALS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckInteract();
}

void ALS_Character::CheckInteract()
{
	FVector Start = FollowCamera->GetComponentLocation();
	FVector Foward = FollowCamera->GetForwardVector();
	FVector End = Start + (Foward * InteractDistance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<ULS_Interactable>())
		{
			if (CurrentInteract != HitActor)
			{
				CurrentInteract = HitActor;
			}

			if (ILS_Interactable* Interactable = Cast<ILS_Interactable>(CurrentInteract))
			{
				Interactable->ShowInteractionUI();
			}
			return;
		}
	}

	if (CurrentInteract)
	{
		if (ILS_Interactable* Interactable = Cast<ILS_Interactable>(CurrentInteract))
		{
			Interactable->HideInteractionUI();
		}
		CurrentInteract = nullptr;
	}
}

void ALS_Character::EquipItem(ALS_BaseItem* Item)
{
	if (!Item || !AbilitySystemComponent) return;

	FGameplayTag EquipTag = Item->GetEquipTag();
	if (EquipTag.IsValid())
	{
		AbilitySystemComponent->AddLooseGameplayTag(EquipTag);
		AbilitySystemComponent->SetTagMapCount(EquipTag, 1);
		UE_LOG(LogTemp, Log, TEXT("Equipped Item: %s"), *EquipTag.ToString());
	}

	EEquipmentSlot Slot = Item->GetEquipmentSlot();
	EquippedItems.Add(Slot, Item);

	Item->DisableCollision();
}

void ALS_Character::UnequipItem(ALS_BaseItem* Item)
{
	if (!Item || !AbilitySystemComponent) return;

	FGameplayTag EquipTag = Item->GetEquipTag();
	if (EquipTag.IsValid())
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(EquipTag);
		UE_LOG(LogTemp, Log, TEXT("Unequipped Item: %s"), *EquipTag.ToString());
	}

	EEquipmentSlot Slot = Item->GetEquipmentSlot();
	if (EquippedItems.Contains(Slot))
	{
		EquippedItems.Remove(Slot);
	}

	Item->EnableCollision();
}

ALS_BaseItem* ALS_Character::GetEquippedItem(EEquipmentSlot Slot) const
{
	if (EquippedItems.Contains(Slot))
	{
		return EquippedItems[Slot];
	}
	return nullptr;
}

bool ALS_Character::IsItemEquipped(EEquipmentSlot Slot) const
{
	return EquippedItems.Contains(Slot) && EquippedItems[Slot] != nullptr;
}

void ALS_Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (InputConfig)
	{
		InputConfig->OnControllerChanged();
	}
}

void ALS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputConfig)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			InputConfig->SetupInput(EnhancedInputComponent);
		}
	}
}

