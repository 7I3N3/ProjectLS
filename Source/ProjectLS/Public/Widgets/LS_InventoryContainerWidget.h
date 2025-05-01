#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryContainerWidget.generated.h"

class UBorder;
class UCanvasPanel;
class ULS_InventorySlotWidget;

UCLASS()
class PROJECTLS_API ULS_InventoryContainerWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BorderFrame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SlotCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventorySlotWidget> SlotWidgetClass;

	TArray<TObjectPtr<ULS_InventorySlotWidget>> SlotWidgets;

	int32 ContainerIndex = -1;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	void InitializeContainerWidget(int32 InContainerIndex, const FIntPoint GridSize, const float SlotSize);

	int32 GetContainerIndex() const { return ContainerIndex; }

	TArray<ULS_InventorySlotWidget*> GetItemSlotWidgets() const { return SlotWidgets; }

#pragma endregion Functions
};