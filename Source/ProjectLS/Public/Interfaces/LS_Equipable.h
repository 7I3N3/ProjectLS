// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LS_Equipable.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
	ES_Head UMETA(DisplayName = "Head"),
	ES_Chest UMETA(DisplayName = "Chest"),
	ES_MainWeapon UMETA(DisplayName = "MainWeapon"),
	ES_SubWeapon UMETA(DisplayName = "SubWeapon"),
	ES_Rig UMETA(DisplayName = "Rig"),
	ES_Bag UMETA(DisplayName = "Bag")
};

class ALS_Character;

UINTERFACE(MinimalAPI)
class ULS_Equipable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTLS_API ILS_Equipable
{
	GENERATED_BODY()

#pragma region Functions
private:


protected:


public:
	virtual void Equip(ALS_Character* Wearer) = 0;
	virtual void Unequip(ALS_Character* Wearer) = 0;

	virtual EEquipmentSlotType GetSlotType() const = 0;
	virtual bool IsEquipped() const = 0;

#pragma endregion Functions
};

USTRUCT(Atomic, BlueprintType)
struct FEquipmentSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentSlotType Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TScriptInterface<ILS_Equipable> Item;
};
