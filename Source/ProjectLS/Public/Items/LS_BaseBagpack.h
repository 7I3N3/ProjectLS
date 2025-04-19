#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseBagpack.generated.h"

class ULS_InventoryComponent;
class ULS_InventoryWidget;

UCLASS()
class PROJECTLS_API ALS_BaseBagpack : public ALS_BaseItem, public ILS_Equipable
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULS_InventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<ULS_InventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	EEquipmentSlotType SlotType;

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

	void ShowInventoryUI(APlayerController* PC);
	void HideInventoryUI(APlayerController* PC);

	ULS_InventoryWidget* GetInventoryWidget() const { return InventoryWidget; }

#pragma endregion Functions
};
