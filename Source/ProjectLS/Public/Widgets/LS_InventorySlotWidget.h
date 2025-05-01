#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_InventorySlotWidget.generated.h"

class ALS_BaseItem;
class ULS_ItemWidget;
class UCanvasPanel;

UCLASS()
class PROJECTLS_API ULS_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(BlueprintReadOnly)
	FLS_InventorySlot SlotData;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ItemCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_ItemWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FIntPoint SlotCoordinate;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	UFUNCTION(BlueprintCallable)
	void InitializeSlotWidget(const FLS_InventorySlot& NewSlotData, const float SlotSize);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotCoordinate(FIntPoint InCoord);

#pragma endregion Functions
};