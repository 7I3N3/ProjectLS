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

ALS_Character::ALS_Character()
{
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
}

void ALS_Character::BeginPlay()
{
	Super::BeginPlay();
	
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

