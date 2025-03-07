// Fill out your copyright notice in the Description page of Project Settings.


#include "AlternativeAttackInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

UAlternativeAttackInputComponent::UAlternativeAttackInputComponent()
{

}

void UAlternativeAttackInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAlternativeAttackInputComponent::BindInput(class UEnhancedInputComponent* InputComponent)
{
    if (InputComponent && InputAction)
    {
        InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UAlternativeAttackInputComponent::AlternativeAttack);
        InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UAlternativeAttackInputComponent::AlternativeAttackStop);
    }
}

void UAlternativeAttackInputComponent::AlternativeAttack()
{

}
void UAlternativeAttackInputComponent::AlternativeAttackStop()
{

}
