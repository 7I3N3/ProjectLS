#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_Equipable.h"
#include "LS_InventoryOwner.h"
#include "LS_BaseBagpack.generated.h"

class ULS_InventoryComponent;
class ULS_InventoryWidget;

UCLASS()
class PROJECTLS_API ALS_BaseBagpack : public ALS_BaseItem, public ILS_Equipable, public ILS_InventoryOwner
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	TArray<ULS_InventoryComponent*> InventoryComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	EEquipmentSlotType SlotType;

	TObjectPtr<ALS_Character> EquippedCharacter;

	bool bIsEquipped;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseBagpack();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	virtual void Equip(ALS_Character* Wearer) override;
	virtual void Unequip(ALS_Character* Wearer) override;

	virtual EEquipmentSlotType GetSlotType() const override { return SlotType; }
	virtual bool IsEquipped() const override { return bIsEquipped; }

	virtual TArray<ULS_InventoryComponent*> GetInventoryComponents() const override { return InventoryComponents; }

#pragma endregion Functions
};
