// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

UInteractInputComponent::UInteractInputComponent()
{

}

void UInteractInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractInputComponent::BindInput(class UEnhancedInputComponent* InputComponent)
{
	if (InputComponent && InputAction)
	{
		InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UInteractInputComponent::Interact);
		InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UInteractInputComponent::StopInteract);
	}
}

void UInteractInputComponent::Interact()
{

}

void UInteractInputComponent::StopInteract()
{

}