#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_InventorySlotWidget.generated.h"

class UImage;
class UBorder;
class ALS_BaseItem;

UCLASS()
class PROJECTLS_API ULS_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(BlueprintReadOnly)
	FLS_InventorySlot SlotData;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FIntPoint SlotCoordinate;

	int32 ContainerIndex = -1;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	UFUNCTION(BlueprintCallable)
	void SetSlotData(const FLS_InventorySlot& NewSlotData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotCoordinate(FIntPoint InCoord);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetPositionInCanvas(FVector2D Position);

	void SetContainerIndex(int32 NewIndex) { ContainerIndex = NewIndex; }

	int32 GetContainerIndex() const { return ContainerIndex; }

#pragma endregion Functions
};