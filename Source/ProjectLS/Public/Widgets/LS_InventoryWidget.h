#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryWidget.generated.h"

class UGridPanel;
class ULS_InventoryComponent;
class ULS_ItemSlotWidget;

UCLASS()
class PROJECTLS_API ULS_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGridPanel> GridPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<ULS_InventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<ULS_ItemSlotWidget> ItemSlotClass;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(ULS_InventoryComponent* NewComponent);

	UFUNCTION(BlueprintCallable)
	void RefreshGrid();

#pragma endregion Functions
};