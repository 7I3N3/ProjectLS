// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAttackInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "ProjectLS/Public/Item/LS_BaseItem.h"
#include "ProjectLS/Public/Item/LS_BaseGun.h"
#include "ProjectLS/Public/LS_Character.h"

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
    ALS_Character* Character = Cast<ALS_Character>(GetOwner());

    if (!Character)
    {
        return;
    }

    if (Character->IsItemEquipped(EEquipmentSlot::MainWeapon))
    {
        ALS_BaseItem* EquppedItem = Character->GetEquippedItem(EEquipmentSlot::MainWeapon);
        if (!EquppedItem)
        {
            return;
        }

        ALS_BaseGun* Gun = Cast<ALS_BaseGun>(EquppedItem);
        if (!Gun)
        {
            return;
        }

        Gun->Fire();

        UE_LOG(LogTemp, Warning, TEXT("Fire Weapon: %s"), *Gun->GetName());
    }
}
void UPrimaryAttackInputComponent::PrimaryAttackStop()
{
    ALS_Character* Character = Cast<ALS_Character>(GetOwner());

    if (!Character)
    {
        return;
    }


}
