// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LS_Equipable.h"
#include "LS_BaseItem.h"
#include "LS_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FLS_InventorySlot
{
	GENERATED_BODY()

	bool bIsOccupied = false;

	TObjectPtr<ALS_BaseItem> OccupyingItem;
};

USTRUCT(BlueprintType)
struct FLS_InventoryContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridOffset;

	TArray<FLS_InventorySlot> InventorySlots;

	void Initialize(FIntPoint NewGridSize, FIntPoint NewGridOffset)
	{
		GridSize = NewGridSize;
		GridOffset = NewGridOffset;
		InventorySlots.SetNum(GridSize.X * GridSize.Y);
	}

	int32 GetIndex(FIntPoint Grid) const { return Grid.Y * GridSize.X + Grid.X; }

	bool CanPlaceItem(FIntPoint StartPos, ALS_BaseItem* Item) const
	{
		if (StartPos.X + Item->GetItemSize().X > GridSize.X || StartPos.Y + Item->GetItemSize().Y > GridSize.Y)
			return false;

		for (int32 y = 0; y < Item->GetItemSize().Y; ++y)
		{
			for (int32 x = 0; x < Item->GetItemSize().X; ++x)
			{
				int32 Index = GetIndex({ StartPos.X + x, StartPos.Y + y });
				if (InventorySlots.IsValidIndex(Index) && InventorySlots[Index].bIsOccupied)
					return false;
			}
		}
		return true;
	}

	void PlaceItem(FIntPoint StartPos, ALS_BaseItem* Item)
	{
		for (int32 y = 0; y < Item->GetItemSize().Y; ++y)
		{
			for (int32 x = 0; x < Item->GetItemSize().X; ++x)
			{
				int32 Index = GetIndex({StartPos.X + x, StartPos.Y + y});
				if (InventorySlots.IsValidIndex(Index))
				{
					InventorySlots[Index].bIsOccupied = true;
					InventorySlots[Index].OccupyingItem = Item;
				}
			}
		}
	}

	void RemoveItem(ALS_BaseItem* Item)
	{
		for (auto& Slot : InventorySlots)
		{
			if (Slot.OccupyingItem == Item)
			{
				Slot.bIsOccupied = false;
				Slot.OccupyingItem = nullptr;
			}
		}
	}

};

UCLASS(config=Game, meta = (BlueprintSpawnableComponent))
class PROJECTLS_API ULS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FIntPoint> GridSizes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FIntPoint> GridOffsets;

	TArray<FLS_InventoryContainer> Containers;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	ULS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	void InitializeInventory();

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(ALS_BaseItem* Item);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(ALS_BaseItem* Item);

	TArray<FLS_InventoryContainer> GetInventoryContainers() const { return Containers; }

	TArray<FIntPoint> GetGridSizes() const { return GridSizes; }

#pragma endregion Functions
};

