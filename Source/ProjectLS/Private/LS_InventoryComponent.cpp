#include "LS_InventoryComponent.h"
#include "LS_BaseItem.h"

ULS_InventoryComponent::ULS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULS_InventoryComponent::InitializeGrid()
{
	ItemGrid.SetNum(GridSize.X);
	for (int32 X = 0; X < GridSize.X; ++X)
	{
		ItemGrid[X].SetNum(GridSize.Y);
		for (int32 Y = 0; Y < GridSize.Y; ++Y)
		{
			ItemGrid[X][Y] = FItemSlotData{ nullptr, FIntPoint(X, Y) };
		}
	}
}

bool ULS_InventoryComponent::CanPlaceItemAt(ALS_BaseItem* Item, FIntPoint StartPos) const
{
	if (!Item) return false;

	FIntPoint ItemSize = Item->GetItemSize();

	// 범위 초과 체크
	if (StartPos.X + ItemSize.X > GridSize.X || StartPos.Y + ItemSize.Y > GridSize.Y)
		return false;

	for (int32 X = 0; X < ItemSize.X; ++X)
	{
		for (int32 Y = 0; Y < ItemSize.Y; ++Y)
		{
			int32 GridX = StartPos.X + X;
			int32 GridY = StartPos.Y + Y;

			if (!ItemGrid.IsValidIndex(GridX) || !ItemGrid[GridX].IsValidIndex(GridY))
				return false;

			if (ItemGrid[GridX][GridY].Item != nullptr)
				return false;
		}
	}

	return true;
}

bool ULS_InventoryComponent::PlaceItem(ALS_BaseItem* Item, FIntPoint StartPos)
{
	if (!CanPlaceItemAt(Item, StartPos))
		return false;

	FIntPoint ItemSize = Item->GetItemSize();

	for (int32 X = 0; X < ItemSize.X; ++X)
	{
		for (int32 Y = 0; Y < ItemSize.Y; ++Y)
		{
			int32 GridX = StartPos.X + X;
			int32 GridY = StartPos.Y + Y;

			ItemGrid[GridX][GridY].Item = Item;
			ItemGrid[GridX][GridY].SlotPos = StartPos;
		}
	}

	return true;
}

void ULS_InventoryComponent::RemoveItemAt(FIntPoint StartPos)
{
	if (!ItemGrid.IsValidIndex(StartPos.X) || !ItemGrid[StartPos.X].IsValidIndex(StartPos.Y))
		return;

	ALS_BaseItem* TargetItem = ItemGrid[StartPos.X][StartPos.Y].Item;
	if (!TargetItem) return;

	FIntPoint ItemSize = TargetItem->GetItemSize();

	for (int32 X = 0; X < ItemSize.X; ++X)
	{
		for (int32 Y = 0; Y < ItemSize.Y; ++Y)
		{
			int32 GridX = StartPos.X + X;
			int32 GridY = StartPos.Y + Y;

			if (ItemGrid[GridX][GridY].Item == TargetItem)
			{
				ItemGrid[GridX][GridY].Item = nullptr;
			}
		}
	}
}

TArray<FItemSlotData> ULS_InventoryComponent::GetAllItems() const
{
	TSet<ALS_BaseItem*> SeenItems;
	TArray<FItemSlotData> UniqueItems;

	for (int32 X = 0; X < GridSize.X; ++X)
	{
		for (int32 Y = 0; Y < GridSize.Y; ++Y)
		{
			const FItemSlotData& Slot = ItemGrid[X][Y];
			if (Slot.Item && !SeenItems.Contains(Slot.Item))
			{
				SeenItems.Add(Slot.Item);
				UniqueItems.Add(Slot);
			}
		}
	}

	return UniqueItems;
}