#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_PlayerStatusWidget.generated.h"

class UScrollBox;
class ULS_PlayerEquipmentWidget;
class ULS_InventoryWidget;

UCLASS()
class PROJECTLS_API ULS_PlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	//�÷��̾� ���� hp, �����, ����, ��

	UPROPERTY(meta = (BindWidget))
	UScrollBox* InventoryScrollBox;

	UPROPERTY(meta = (BindWidget))
	ULS_PlayerEquipmentWidget* EquipmentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventoryWidget> InventoryWidgetClass;

	TArray<ULS_InventoryWidget*> Inventories;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetupEquipmentAndInventories(const TMap<EEquipmentSlotType, TScriptInterface<ILS_Equipable>>& EquippedItems);

	ULS_PlayerEquipmentWidget* GetEquipmentWidget() const { return EquipmentWidget; }

	TArray<ULS_InventoryWidget*> GetInventories() const { return Inventories; }

#pragma endregion Functions
};