#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_ItemSlotWidget.generated.h"

class UImage;
class UTextBlock;
class ALS_BaseItem;

UCLASS()
class PROJECTLS_API ULS_ItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TObjectPtr<ALS_BaseItem> ItemRef;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetItem(ALS_BaseItem* NewItem);

	UFUNCTION(BlueprintPure)
	ALS_BaseItem* GetItem() const { return ItemRef; }

#pragma endregion Functions
};