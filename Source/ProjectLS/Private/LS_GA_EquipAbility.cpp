// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_GA_EquipAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "LS_BaseItem.h"

ULS_GA_EquipAbility::ULS_GA_EquipAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULS_GA_EquipAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    AActor* OwnerActor = ActorInfo->OwnerActor.Get();
    const ALS_BaseItem* EquippedItem = Cast<ALS_BaseItem>(TriggerEventData->Target);

    if (EquippedItem)
    {
        FGameplayTagContainer Tags;
        Tags.AddTag(EquippedItem->GetEquipTag());

        ActorInfo->AbilitySystemComponent->AddLooseGameplayTags(Tags);
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}