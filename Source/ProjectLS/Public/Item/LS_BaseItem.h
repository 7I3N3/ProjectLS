// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "LS_Interactable.h"
#include "LS_BaseItem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	None			UMETA(DisplayName = "None"),
	MainWeapon		UMETA(DisplayName = "MainWeapon"),		// 주 무기
	SubWeapon		UMETA(DisplayName = "SubWeapon"),		// 보조 무기
	MeleeWeapon		UMETA(DisplayName = "MeleeWeapon"),		// 근접 무기
	HeadGear		UMETA(DisplayName = "HeadGear"),		// 머리 보호구
	Goggles			UMETA(DisplayName = "Goggles"),			// 보호 안경
	ChestArmor		UMETA(DisplayName = "ChestArmor"),		// 방탄복
	ChestRig		UMETA(DisplayName = "ChestRig"),		// 리그
	Headset			UMETA(DisplayName = "Headset")			// 헤드셋
};

UCLASS()
class PROJECTLS_API ALS_BaseItem : public AActor, public ILS_Interactable
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	EEquipmentSlot EquipmentSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FGameplayTag EquipTag;

	bool bIsUIVisible;

public:

#pragma endregion Parameters

#pragma region Functions
private:
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ALS_BaseItem();

	virtual void Interact(AActor* Interactor) override;
	virtual void ShowInteractionUI() override;
	virtual void HideInteractionUI() override;

	FORCEINLINE EEquipmentSlot GetEquipmentSlot() const { return EquipmentSlot; }
	FORCEINLINE FGameplayTag GetEquipTag() const { return EquipTag; }

#pragma endregion Functions

};
