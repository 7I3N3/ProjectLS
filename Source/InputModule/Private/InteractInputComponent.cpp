// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "ProjectLS/Public/LS_Character.h"
#include "ProjectLS/Public/LS_Interactable.h"

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
	}
}

void UInteractInputComponent::Interact()
{
	ALS_Character* Character = Cast<ALS_Character>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is nullptr"));
		return;
	}

	AActor* CurrentInteract = Character->CurrentInteract;
	if (CurrentInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("No interactable actor found"));
		return;
	}

	ILS_Interactable* Interactable = Cast<ILS_Interactable>(CurrentInteract);
	if (!Interactable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor does not implement ILS_Interactable"));
		return;
	}

	Interactable->Interact(Character);
}
