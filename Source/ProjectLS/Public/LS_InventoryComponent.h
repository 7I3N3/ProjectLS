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

	TObjectPtr<ALS_BaseItem> OccupyingItem = nullptr;
	bool bIsRoot = false;

	bool CanStack(ALS_BaseItem* NewItem) const { return OccupyingItem && OccupyingItem->CanStackWith(NewItem) && !OccupyingItem->IsFullStack(); }
};

USTRUCT(BlueprintType)
struct FLS_InventoryContainer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryContainer", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridSize = { 1, 1 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryContainer", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridOffset = { 0, 0 };

	FVector2D ScreenPosition;

	TArray<FLS_InventorySlot> InventorySlots;

	void InitializeContainer()
	{
		InventorySlots.SetNum(GridSize.X * GridSize.Y);
	}

	int32 GetIndex(FIntPoint GridPos) const { return GridPos.Y * GridSize.X + GridPos.X; }
	int32 GetIndex(int32 GridPosX, int32 GridPosY) const { return GridPosY * GridSize.X + GridPosX; }

	bool CanPlaceItem(ALS_BaseItem* Item, int32 StartPosX, int32 StartPosY) const
	{
		if (StartPosX + Item->GetItemSize().X > GridSize.X || StartPosY + Item->GetItemSize().Y > GridSize.Y)
			return false;

		for (int32 y = 0; y < Item->GetItemSize().Y; ++y)
		{
			for (int32 x = 0; x < Item->GetItemSize().X; ++x)
			{
				int32 Index = GetIndex({ StartPosX + x, StartPosY + y });
				if (!InventorySlots.IsValidIndex(Index) || InventorySlots[Index].OccupyingItem)
					return false;
			}
		}
		return true;
	}
	bool CanPlaceItem(ALS_BaseItem* Item, FIntPoint StartPos) const
	{
		return CanPlaceItem(Item, StartPos.X, StartPos.Y);
	}

	bool TryAddItem(ALS_BaseItem* NewItem)
	{
		if (NewItem->IsStackable())
		{
			for (auto& Slot : InventorySlots)
			{
				if (Slot.CanStack(NewItem))
				{
					int32 AddAmount = FMath::Min(NewItem->GetCurrentStackCount(), Slot.OccupyingItem->GetMaxStackCount() - Slot.OccupyingItem->GetCurrentStackCount());
					Slot.OccupyingItem->AddStack(AddAmount);
					NewItem->AddStack(-AddAmount);

					if (NewItem->GetCurrentStackCount() <= 0)
						return true;
				}
			}
		}

		for (int32 y = 0; y <= GridSize.Y - NewItem->GetItemSize().Y; ++y)
		{
			for (int32 x = 0; x <= GridSize.X - NewItem->GetItemSize().X; ++x)
			{
				if (CanPlaceItem(NewItem, x, y))
				{
					PlaceItem(NewItem, x, y);
					return true;
				}
			}
		}

		return false;
	}

	bool TryPlaceItemAt(ALS_BaseItem* Item, int32 StartGridX, int32 StartGridY)
	{
		if (CanPlaceItem(Item, StartGridX, StartGridY))
		{
			PlaceItem(Item, StartGridX, StartGridY);
			return true;
		}
		return false;
	}
	bool TryPlaceItemAt(ALS_BaseItem* Item, FIntPoint StartGrid)
	{
		return TryPlaceItemAt(Item, StartGrid.X, StartGrid.Y);
	}

	void PlaceItem(ALS_BaseItem* Item, int32 StartGridX, int32 StartGridY)
	{
		for (int32 GridY = 0; GridY < Item->GetItemSize().Y; GridY++)
		{
			for (int32 GridX = 0; GridX < Item->GetItemSize().X; GridX++)
			{
				int32 Index = GetIndex(StartGridX + GridX, StartGridY + GridY);

				if (InventorySlots.IsValidIndex(Index))
				{
					FLS_InventorySlot& Slot = InventorySlots[Index];
					Slot.OccupyingItem = Item;
					Slot.bIsRoot = (GridX == 0 && GridY == 0);
				}
			}
		}
	}
	void PlaceItem(ALS_BaseItem* Item, FIntPoint StartGrid)
	{
		PlaceItem(Item, StartGrid.X, StartGrid.Y);
	}

	void RemoveItem(ALS_BaseItem* Item)
	{
		for (FLS_InventorySlot& Slot : InventorySlots)
		{
			if (Slot.OccupyingItem == Item)
			{
				Slot.OccupyingItem = nullptr;
				Slot.bIsRoot = false;
			}
		}
	}

	bool IsRootSlot(int32 Index) const { return InventorySlots.IsValidIndex(Index) && InventorySlots[Index].bIsRoot; }

	FIntPoint GetSlotLocalPosition(int Index) const
	{
		if (!InventorySlots.IsValidIndex(Index))
			return FIntPoint::ZeroValue;

		int32 LocalX = Index % GridSize.X;
		int32 LocalY = Index / GridSize.X;

		return FIntPoint(LocalX, LocalY);
	}
	FIntPoint GetSlotWorldPosition(int Index) const
	{
		if (!InventorySlots.IsValidIndex(Index))
			return FIntPoint::ZeroValue;

		return GridOffset + GetSlotLocalPosition(Index);
	}
};

USTRUCT(Atomic)
struct FLS_ItemPlacementInfo
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ContainerIndex;

	UPROPERTY()
	FIntPoint StartPos;
};

UCLASS(config=Game, meta = (BlueprintSpawnableComponent))
class PROJECTLS_API ULS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FLS_InventoryContainer> Containers;

	TMap<ALS_BaseItem*, FLS_ItemPlacementInfo> ItemMap;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	

public:
	ULS_InventoryComponent();

	void InitializeInventory();

	bool TryAddItem(ALS_BaseItem* Item);

	bool TryPlaceItemAt(ALS_BaseItem* Item, int32 ContainerIndex, int32 StartPosX, int32 StartPosY);
	bool TryPlaceItemAt(ALS_BaseItem* Item, int32 ContainerIndex, FIntPoint StartPos)
	{
		return TryPlaceItemAt(Item, ContainerIndex, StartPos.X, StartPos.Y);
	}

	void RemoveItem(ALS_BaseItem* Item);

	bool CanPlaceItem(ALS_BaseItem* Item, int32 ContainerIndex, FIntPoint StartPos) const
	{
		return CanPlaceItem(Item, ContainerIndex, StartPos.X, StartPos.Y);
	}
	bool CanPlaceItem(ALS_BaseItem* Item, int32 ContainerIndex, int32 StartPosX, int32 StartPosY) const;
	

	bool FindPlacement(ALS_BaseItem* Item, int32& OutContainerIndex, FIntPoint& OutStartPos) const;

	ALS_BaseItem* GetItemAt(int32 ContainerIndex, FIntPoint StartPos) const;

	FORCEINLINE TArray<FLS_InventoryContainer> GetContainers() const { return Containers; }

	#pragma endregion Functions
};

