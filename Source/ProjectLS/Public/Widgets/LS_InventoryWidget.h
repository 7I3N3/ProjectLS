#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryWidget.generated.h"

class UCanvasPanel;
class ULS_ItemWidget;
class ULS_InventoryComponent;
class ULS_InventoryContainerWidget;

class ALS_BaseItem;

UCLASS()
class PROJECTLS_API ULS_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ContainerCanvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ItemCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventoryContainerWidget> ContainerWidgetClass;

	TArray<TObjectPtr<ULS_InventoryContainerWidget>> ContainerWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_ItemWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<ULS_InventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float SlotSize = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float ContainerPadding = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float ContainerBorder = 4.0f;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void InitializeInventory(ULS_InventoryComponent* NewComponent);

	UFUNCTION(BlueprintCallable)
	void RefreshInventory();

	void PositionItemWidget(ULS_ItemWidget* ItemWidget, FIntPoint RootSlotCoord);

	UFUNCTION(BlueprintCallable)
	void HandleItemDrop(ULS_ItemWidget* DraggedItemWidget, const FVector2D DropPosition);

	UFUNCTION(BlueprintCallable)
	bool TakeItem(ALS_BaseItem* Item);

	UFUNCTION(BlueprintCallable)
	bool DumpItem(ALS_BaseItem* Item);

	int32 FindContainerIndexAtPosition(const FVector2D& DropPosition) const;

	void DebugInventory();

#pragma endregion Functions
};