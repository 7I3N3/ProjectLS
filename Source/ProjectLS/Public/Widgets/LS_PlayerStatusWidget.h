#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_PlayerStatusWidget.generated.h"

class UVerticalBox;
class ULS_PlayerEquipmentWidget;
class ULS_InventoryWidget;

UCLASS()
class PROJECTLS_API ULS_PlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	//플레이어 스탯 hp, 배고픔, 수분, 등

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* InventoryContainer;

	UPROPERTY(meta = (BindWidget))
	ULS_PlayerEquipmentWidget* EquipmentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventoryWidget> InventoryWidgetClass;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetupEquipmentAndInventories(const TMap<EEquipmentSlotType, TScriptInterface<ILS_Equipable>>& EquippedItems);

	ULS_PlayerEquipmentWidget* GetEquipmentWidget() const { return EquipmentWidget; }

#pragma endregion Functions
};