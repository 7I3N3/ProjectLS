#include "LS_InventoryComponent.h"
#include "LS_BaseItem.h"

ULS_InventoryComponent::ULS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULS_InventoryComponent::InitializeInventory()
{
	for (FLS_InventoryContainer& Container : Containers)
	{
		Container.InitializeContainer();
	}
}

bool ULS_InventoryComponent::TryAddItem(ALS_BaseItem* Item)
{
	if (!Item) return false;

	int32 FoundContainerIndex = -1;
	FIntPoint StartPos;

	if (!FindPlacement(Item, FoundContainerIndex, StartPos))
		return false;

	FLS_InventoryContainer& TargetContainer = Containers[FoundContainerIndex];
	TargetContainer.PlaceItem(Item, StartPos);

	ItemMap.Add(Item, { FoundContainerIndex, StartPos });
	return true;
}

bool ULS_InventoryComponent::TryPlaceItemAt(ALS_BaseItem* Item, int32 ContainerIndex, int32 StartPosX, int32 StartPosY)
{
	if (!Item || !Containers.IsValidIndex(ContainerIndex))
		return false;

	FLS_InventoryContainer& Container = Containers[ContainerIndex];

	FIntPoint StartPos = FIntPoint(StartPosX, StartPosY);

	if (!Container.CanPlaceItem(Item, StartPos))
		return false;

	Container.PlaceItem(Item, StartPos);
	ItemMap.Add(Item, { ContainerIndex, StartPos });
	return true;
}

void ULS_InventoryComponent::RemoveItem(ALS_BaseItem* Item)
{
	if (!Item || !ItemMap.Contains(Item)) return;

	const FLS_ItemPlacementInfo& Info = ItemMap[Item];
	if (Containers.IsValidIndex(Info.ContainerIndex))
	{
		Containers[Info.ContainerIndex].RemoveItem(Item);
	}

	ItemMap.Remove(Item);
}

bool ULS_InventoryComponent::CanPlaceItem(ALS_BaseItem* Item, int32 ContainerIndex, int32 StartPosX, int32 StartPosY) const
{
	if (!Item || Containers.IsValidIndex(ContainerIndex)) return false;

	return Containers[ContainerIndex].CanPlaceItem(Item, StartPosX, StartPosY);
}

bool ULS_InventoryComponent::FindPlacement(ALS_BaseItem* Item, int32& OutContainerIndex, FIntPoint& OutStartPos) const
{
	for (int32 i = 0; i < Containers.Num(); ++i)
	{
		const FLS_InventoryContainer& Container = Containers[i];

		for (int32 y = 0; y <= Container.GridSize.Y - Item->GetItemSize().Y; ++y)
		{
			for (int32 x = 0; x <= Container.GridSize.X - Item->GetItemSize().X; ++x)
			{
				FIntPoint Pos(x, y);
				if (Container.CanPlaceItem(Item, Pos))
				{
					OutContainerIndex = i;
					OutStartPos = Pos;
					return true;
				}
			}
		}
	}
	return false;
}

ALS_BaseItem* ULS_InventoryComponent::GetItemAt(int32 ContainerIndex, FIntPoint GridPos) const
{
	if (!Containers.IsValidIndex(ContainerIndex))
		return nullptr;

	const FLS_InventoryContainer& Container = Containers[ContainerIndex];

	int32 Index = Container.GetIndex(GridPos);
	if (!Container.InventorySlots.IsValidIndex(Index))
		return nullptr;

	return Container.InventorySlots[Index].OccupyingItem;
}