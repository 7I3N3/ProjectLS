#include "LS_InventoryComponent.h"
#include "LS_BaseItem.h"

ULS_InventoryComponent::ULS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULS_InventoryComponent::InitializeInventory()
{
	if (GridSizes.Num() != GridOffsets.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Dosent match GridSizes.Num(), GridOffsets.Num()"));
		return;
	}
	Containers.Empty();

	for (int32 Index = 0; Index < GridSizes.Num(); Index++)
	{
		const FIntPoint GridSize = GridSizes[Index];
		const FIntPoint GridOffset = GridOffsets[Index];

		FLS_InventoryContainer Container;
		Container.Initialize(GridSize, GridOffset);
		Containers.Add(Container);
	}
}

bool ULS_InventoryComponent::TryAddItem(ALS_BaseItem* Item)
{
	for (FLS_InventoryContainer& Container : Containers)
	{
		for (int32 y = 0; y < Container.GridSize.Y; ++y)
		{
			for (int32 x = 0; x < Container.GridSize.X; ++x)
			{
				if (Container.CanPlaceItem({x, y}, Item))
				{
					Container.PlaceItem({ x, y }, Item);
					return true;
				}
			}
		}
	}
	return false;
}

void ULS_InventoryComponent::RemoveItem(ALS_BaseItem* Item)
{
	for (FLS_InventoryContainer& Container : Containers)
	{
		Container.RemoveItem(Item);
	}
}