// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAttackInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

UPrimaryAttackInputComponent::UPrimaryAttackInputComponent()
{

}

void UPrimaryAttackInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPrimaryAttackInputComponent::BindInput(class UEnhancedInputComponent* InputComponent)
{
    if (InputComponent && InputAction)
    {
        InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UPrimaryAttackInputComponent::PrimaryAttack);
        InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UPrimaryAttackInputComponent::PrimaryAttackStop);
    }
}


void UPrimaryAttackInputComponent::PrimaryAttack()
{

}
void UPrimaryAttackInputComponent::PrimaryAttackStop()
{

}
