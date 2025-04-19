// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LS_Equipable.h"
#include "LS_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemSlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALS_BaseItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FIntPoint SlotPos;
};

UCLASS(config=Game)
class PROJECTLS_API ULS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridSize;

	TArray<TArray<FItemSlotData>> ItemGrid;


public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	ULS_InventoryComponent();

	void InitializeGrid();

	UFUNCTION(BlueprintCallable)
	bool CanPlaceItemAt(ALS_BaseItem* Item, FIntPoint StartPos) const;

	UFUNCTION(BlueprintCallable)
	bool PlaceItem(ALS_BaseItem* Item, FIntPoint StartPos);

	UFUNCTION(BlueprintCallable)
	void RemoveItemAt(FIntPoint StartPos);

	UFUNCTION(BlueprintCallable)
	TArray<FItemSlotData> GetAllItems() const;

	FIntPoint GetGridSize() const { return GridSize; }

#pragma endregion Functions
};

