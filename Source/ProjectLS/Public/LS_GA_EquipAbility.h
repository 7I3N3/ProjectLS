// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LS_BaseItem.h"
#include "LS_GA_EquipAbility.generated.h"

UCLASS()
class PROJECTLS_API ULS_GA_EquipAbility : public UGameplayAbility
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	EEquipmentSlot SlotType;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	ULS_GA_EquipAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

#pragma endregion Functions
};
