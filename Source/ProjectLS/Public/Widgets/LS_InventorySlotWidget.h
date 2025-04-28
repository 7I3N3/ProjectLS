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

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	UFUNCTION(BlueprintCallable)
	void SetSlotData(const FLS_InventorySlot& NewSlotData);

#pragma endregion Functions
};