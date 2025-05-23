// Copyright Epic Games, Inc. All Rights Reserved.

#include "LS_Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LS_Interactable.h"
#include "LS_BaseGun.h"
#include "LS_InteractionMenuWidget.h"
#include "LS_PlayerStatusWidget.h"
#include "LS_InventoryWidget.h"
#include "Blueprint/UserWidget.h"

ALS_Character::ALS_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), TEXT("head"));
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	LookRotator = FRotator::ZeroRotator;
}

void ALS_Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	if (InteractionMenuClass)
	{
		InteractionMenu = CreateWidget<ULS_InteractionMenuWidget>(PC, InteractionMenuClass);
		if (InteractionMenu)
		{
			InteractionMenu->AddToViewport();
			InteractionMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (PlayerStatusClass)
	{
		PlayerStatus = CreateWidget<ULS_PlayerStatusWidget>(PC, PlayerStatusClass);
		if (PlayerStatus)
		{
			PlayerStatus->AddToViewport();
			PlayerStatus->SetVisibility(ESlateVisibility::Hidden);

			UpdateStatus();
		}
	}
}

void ALS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + (FollowCamera->GetForwardVector() * 300.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, FollowCamera->GetComponentLocation(), End, ECC_Visibility))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<ULS_Interactable>())
		{
			ILS_Interactable* Interactable = Cast<ILS_Interactable>(HitActor);
			if (Interactable)
			{
				if (Interactable == CurrentInteractable) return;

				CurrentInteractable = Interactable;

				TArray<FString> InteractionOptionStrings;
				CurrentInteractable->GetInteractionOptions().GetKeys(InteractionOptionStrings);
				InteractionMenu->UpdateMenu(InteractionOptionStrings);
				InteractionMenu->SetVisibility(ESlateVisibility::Visible);
				return;
			}
		}
	}

	if (CurrentInteractable)
	{
		InteractionMenu->SetVisibility(ESlateVisibility::Hidden);
		CurrentInteractable = nullptr;
	}
}

void ALS_Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ALS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALS_Character::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALS_Character::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ALS_Character::Interact);

		EnhancedInputComponent->BindAction(SelectInteractionOptionAction, ETriggerEvent::Triggered, this, &ALS_Character::SelectInteractionOption);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ALS_Character::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ALS_Character::StopShoot);

		EnhancedInputComponent->BindAction(Quickslot1Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot1);
		EnhancedInputComponent->BindAction(Quickslot2Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot2);
		EnhancedInputComponent->BindAction(Quickslot3Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot3);
		EnhancedInputComponent->BindAction(Quickslot4Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot4);
		EnhancedInputComponent->BindAction(Quickslot5Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot5);
		EnhancedInputComponent->BindAction(Quickslot6Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot6);
		EnhancedInputComponent->BindAction(Quickslot7Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot7);
		EnhancedInputComponent->BindAction(Quickslot8Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot8);
		EnhancedInputComponent->BindAction(Quickslot9Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot9);
		EnhancedInputComponent->BindAction(Quickslot0Action, ETriggerEvent::Triggered, this, &ALS_Character::SelectQuickslot0);

		EnhancedInputComponent->BindAction(PlayerStatusToggleAction, ETriggerEvent::Started, this, &ALS_Character::PlayerStatusToggle);
	}
}

void ALS_Character::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALS_Character::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		LookRotator.Pitch = FMath::Clamp(LookRotator.Pitch + (LookAxisVector.Y * 0.4f), -12.0f, 15.0f);
		LookRotator.Yaw = FMath::Clamp(LookRotator.Yaw + (LookAxisVector.X * 0.25f), -15.0f, 15.0f);
	}
}

void ALS_Character::Interact()
{
	if (Controller && CurrentInteractable && InteractionMenu)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);

		if (PlayerController)
		{
			CurrentInteractable->ExecuteInteraction(*InteractionMenu->GetSelectedOptionString(), PlayerController);
		}
	}
}

void ALS_Character::SelectInteractionOption(const FInputActionValue& Value)
{
	if (!CurrentInteractable) return;

	float Scroll = Value.Get<float>();
	if (Scroll == 0) return;

	InteractionMenu->MoveSelection((int32)Scroll);
}

void ALS_Character::Shoot()
{
	if (CurrentWeapon)
	{
		ALS_BaseGun* Gun = Cast<ALS_BaseGun>(CurrentWeapon.GetObject());

		if (Gun)
		{
			Gun->StartFiring();
		}
	}
}

void ALS_Character::StopShoot()
{
	if (CurrentWeapon)
	{
		ALS_BaseGun* Gun = Cast<ALS_BaseGun>(CurrentWeapon.GetObject());

		if (Gun)
		{
			Gun->StopFiring();
		}
	}
}

bool ALS_Character::EquipItem(const TScriptInterface<ILS_Equipable>& Item)
{
	if (!Item) return false;

	EEquipmentSlotType SlotType = Item->GetSlotType();

	if (EquippedItems.Contains(SlotType))
	{
		TScriptInterface<ILS_Equipable> ExistingItem = EquippedItems[SlotType];
		if (ExistingItem)
		{
			ExistingItem->Unequip(this);
		}
	}

	EquippedItems.Add(SlotType, Item);

	UpdateStatus();

	if (SlotType == EEquipmentSlotType::ES_MainWeapon || SlotType == EEquipmentSlotType::ES_SubWeapon)
	{

		CurrentWeapon = Item;
	}

	return true;
}

bool ALS_Character::UnequipItem(EEquipmentSlotType SlotType)
{
	if (!EquippedItems.Contains(SlotType)) return false;

	TScriptInterface<ILS_Equipable> Item = EquippedItems[SlotType];
	if (Item)
	{
		Item->Unequip(this);
	}

	EquippedItems.Remove(SlotType);

	UpdateStatus();

	return true;
}

bool ALS_Character::TakeItem(ALS_BaseItem* Item)
{
	if (!Item) return false;

	for (ULS_InventoryWidget* InventoryWidget : PlayerStatus->GetInventories())
	{
		if (InventoryWidget->TakeItem(Item))
		{
			InventoryWidget->DebugInventory();
			return true;
		}
	}
	return false;
}
bool ALS_Character::DumpItem(ALS_BaseItem* Item)
{
	if (!Item) return false;

	return true;
}

void ALS_Character::SelectQuickslot(int32 SlotIndex)
{
	switch (SlotIndex)
	{
	case 1:
		SwitchWeapon(EEquipmentSlotType::ES_MainWeapon);
		break;

	case 2:
		SwitchWeapon(EEquipmentSlotType::ES_SubWeapon);
		break;

	default:
		UE_LOG(LogTemp, Log, TEXT("QuickSlot %d Selected"), SlotIndex);
		break;
	}
}

void ALS_Character::SelectQuickslot1()
{
	SelectQuickslot(1);
}
void ALS_Character::SelectQuickslot2()
{
	SelectQuickslot(2);
}
void ALS_Character::SelectQuickslot3()
{
	SelectQuickslot(3);
}
void ALS_Character::SelectQuickslot4()
{
	SelectQuickslot(4);
}
void ALS_Character::SelectQuickslot5()
{
	SelectQuickslot(5);
}
void ALS_Character::SelectQuickslot6()
{
	SelectQuickslot(6);
}
void ALS_Character::SelectQuickslot7()
{
	SelectQuickslot(7);
}
void ALS_Character::SelectQuickslot8()
{
	SelectQuickslot(8);
}
void ALS_Character::SelectQuickslot9()
{
	SelectQuickslot(9);
}
void ALS_Character::SelectQuickslot0()
{
	SelectQuickslot(0);
}

void ALS_Character::SwitchWeapon(EEquipmentSlotType TargetSlot)
{
	TScriptInterface<ILS_Equipable> TargetWeapon = EquippedItems.FindRef(TargetSlot);

	if (!TargetWeapon)
		return;

	if (CurrentWeapon == TargetWeapon)
		return;

	if (CurrentWeapon)
	{
		CurrentWeapon->Unequip(this);
	}

	TargetWeapon->Equip(this);
	CurrentWeapon = TargetWeapon;
}

void ALS_Character::PlayerStatusToggle()
{
	if (!PlayerStatus) return;

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	if (bIsPlayerStatusOpen)
	{
		bIsPlayerStatusOpen = false;
		PlayerStatus->SetVisibility(ESlateVisibility::Hidden);

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
	else
	{
		bIsPlayerStatusOpen = true;
		PlayerStatus->SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PlayerStatus->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void ALS_Character::UpdateStatus()
{
	if (PlayerStatus)
	{
		PlayerStatus->SetupEquipmentAndInventories(EquippedItems);
	}
}