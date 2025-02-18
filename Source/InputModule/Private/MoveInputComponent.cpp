// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

UMoveInputComponent::UMoveInputComponent()
{

}

void UMoveInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMoveInputComponent::BindInput(class UEnhancedInputComponent* InputComponent)
{
    if (InputComponent && InputAction)
    {
        InputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UMoveInputComponent::Move);
    }
}

void UMoveInputComponent::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character)
	{
		AController* Controller = Character->Controller;

		if (Controller)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			Character->AddMovementInput(ForwardDirection, MovementVector.Y);
			Character->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}