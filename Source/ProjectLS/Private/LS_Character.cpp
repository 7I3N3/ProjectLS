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
#include "LS_InteractionMenuWidget.h"
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

	if (InteractionMenuClass)
	{
		InteractionMenu = CreateWidget<ULS_InteractionMenuWidget>(GetWorld(), InteractionMenuClass);
		if (InteractionMenu)
		{
			InteractionMenu->AddToViewport();
			InteractionMenu->SetVisibility(ESlateVisibility::Hidden);
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