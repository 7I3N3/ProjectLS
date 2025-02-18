// Fill out your copyright notice in the Description page of Project Settings.


#include "LookInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ULookInputComponent::ULookInputComponent()
{

}

void ULookInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULookInputComponent::BindInput(class UEnhancedInputComponent* InputComponent)
{
    if (InputComponent && InputAction)
    {
        InputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ULookInputComponent::Look);
    }
}

void ULookInputComponent::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character)
	{
		AController* Controller = Character->Controller;

		if (Controller)
		{
			Character->AddControllerYawInput(-LookAxisVector.X);
			Character->AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}