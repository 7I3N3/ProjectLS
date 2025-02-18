// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

UJumpInputComponent::UJumpInputComponent()
{

}

void UJumpInputComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UJumpInputComponent::BindInput(UEnhancedInputComponent* InputComponent)
{
    if (InputComponent && InputAction)
    {
        InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UJumpInputComponent::Jump);
        InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UJumpInputComponent::StopJumping);
    }
}

void UJumpInputComponent::Jump()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (Character)
    {
        Character->bPressedJump = true;
        Character->JumpKeyHoldTime = 0.0f;
    }
}

void UJumpInputComponent::StopJumping()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (Character)
    {
        Character->bPressedJump = false;
        Character->ResetJumpState();
    }
}