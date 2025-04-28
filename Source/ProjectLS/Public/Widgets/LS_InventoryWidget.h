#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryWidget.generated.h"

class UCanvasPanel;
class ULS_InventoryComponent;
class ULS_InventorySlotWidget;

UCLASS()
class PROJECTLS_API ULS_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InventorySlotWidget> InventorySlotWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<ULS_InventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float SlotSize = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float SlotPadding = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float ContainerPadding = 4.0f;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(ULS_InventoryComponent* NewComponent);

	UFUNCTION(BlueprintCallable)
	void RefreshInventory();

#pragma endregion Functions
};