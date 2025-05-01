#include "LS_InventoryWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_InventoryContainerWidget.h"
#include "LS_InventorySlotWidget.h"
#include "LS_ItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"

void ULS_InventoryWidget::InitializeInventory(ULS_InventoryComponent* NewComponent)
{
	InventoryComponent = NewComponent;

	if (!InventoryComponent || !ContainerWidgetClass) return;

	ContainerCanvas->ClearChildren();
	ContainerWidgets.Empty();

	const TArray<FLS_InventoryContainer>& Containers = InventoryComponent->GetContainers();

	for (int32 Index = 0; Index < Containers.Num(); Index++)
	{
		const FIntPoint Offset = Containers[Index].GridOffset;
		const FIntPoint Size = Containers[Index].GridSize;

		if (ULS_InventoryContainerWidget* ContainerWidget = CreateWidget<ULS_InventoryContainerWidget>(this, ContainerWidgetClass))
		{
			ContainerCanvas->AddChild(ContainerWidget);
			ContainerWidget->InitializeContainerWidget(Index, Size, SlotSize);
			ContainerWidgets.Add(ContainerWidget);

			if (UCanvasPanelSlot* ContainerSlot = Cast<UCanvasPanelSlot>(ContainerWidget->Slot))
			{
				ContainerSlot->SetAnchors(FAnchors(0.f, 0.f));
				ContainerSlot->SetAlignment(FVector2D(0.f, 0.f));

				FVector2D ContainerSize = FVector2D(Size) * SlotSize + ContainerBorder;
				FVector2D ContainerPosition = FVector2D(Offset) * SlotSize + ContainerBorder * 2.0f + ContainerPadding * 2.0f;

				ContainerSlot->SetSize(ContainerSize); 
				ContainerSlot->SetPosition(ContainerPosition);
			}
		}
	}
}

void ULS_InventoryWidget::RefreshInventory()
{
	if (!InventoryComponent) return;

	const TArray<FLS_InventoryContainer>& Containers = InventoryComponent->GetContainers();

	for (int32 ContainerIndex = 0; ContainerIndex < Containers.Num(); ++ContainerIndex)
	{
		const FLS_InventoryContainer& Container = Containers[ContainerIndex];

		for (int32 SlotIndex = 0; SlotIndex < Container.InventorySlots.Num(); ++SlotIndex)
		{
			const FLS_InventorySlot& InventorySlot = Container.InventorySlots[SlotIndex];

			ULS_InventorySlotWidget* SlotWidget = ContainerWidgets[ContainerIndex]->GetItemSlotWidgets()[SlotIndex];

			SlotWidget->InitializeSlotWidget(InventorySlot, SlotSize);
		}
	}
}

void ULS_InventoryWidget::HandleItemDrop(ULS_ItemWidget* DraggedItemWidget, const FVector2D DropPosition)
{
	if (!DraggedItemWidget || !InventoryComponent) return;

	ULS_InventoryContainerWidget* TargetContainer = nullptr;

	for (ULS_InventoryContainerWidget* Container : ContainerWidgets)
	{
		if (Container && Container->IsHovered())
		{
			TargetContainer = Container;
			break;
		}
	}

	if (TargetContainer)
	{
		const int32 GridX = FMath::FloorToInt(DropPosition.X / SlotSize);
		const int32 GridY = FMath::FloorToInt(DropPosition.Y / SlotSize);

		const int32 ContainerIndex = TargetContainer->GetContainerIndex();

		if (InventoryComponent->CanPlaceItem(DraggedItemWidget->GetItem(), ContainerIndex, GridX, GridY))
		{
			// 놓을 수 있다면 위치 업데이트
			InventoryComponent->TryPlaceItemAt(DraggedItemWidget->GetItem(), ContainerIndex, GridX, GridY);
			RefreshInventory();
			return;
		}
	}
	RefreshInventory();
}

bool ULS_InventoryWidget::TakeItem(ALS_BaseItem* Item)
{
	if (!Item || !InventoryComponent) return false;

	if (InventoryComponent->TryAddItem(Item))
	{
		RefreshInventory();
		return true;
	}
	return false;
}

bool ULS_InventoryWidget::DumpItem(ALS_BaseItem* Item)
{
	if (!Item || !InventoryComponent) return false;

	return false;
}

void ULS_InventoryWidget::DebugInventory()
{
	for (const FLS_InventoryContainer& Container : InventoryComponent->GetContainers())
	{
		for (int32 y = 0; y < Container.GridSize.Y; y++)
		{
			for (int32 x = 0; x < Container.GridSize.X; x++)
			{
				int32 Index = Container.GetIndex({ x, y });

				if (Container.InventorySlots.IsValidIndex(Index))
				{
					const auto& InventorySlot = Container.InventorySlots[Index];
					if (InventorySlot.OccupyingItem)
					{
						UE_LOG(LogTemp, Log, TEXT("Inventory (%d, %d): %s"), x, y, *InventorySlot.OccupyingItem->GetName());
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("Inventory (%d, %d): Empty"), x, y);
					}
				}
			}
		}
	}
}

int32 ULS_InventoryWidget::FindContainerIndexAtPosition(const FVector2D& DropPosition) const
{
	for (int32 i = 0; i < InventoryComponent->GetContainers().Num(); ++i)
	{
		const FLS_InventoryContainer& Container = InventoryComponent->GetContainers()[i];

		const FVector2D ContainerTopLeft = Container.ScreenPosition;
		const FVector2D ContainerSize = FVector2D(Container.GridSize.X * SlotSize, Container.GridSize.Y * SlotSize);
		const FVector2D ContainerBottomRight = ContainerTopLeft + ContainerSize;

		if (DropPosition.X >= ContainerTopLeft.X && DropPosition.X < ContainerBottomRight.X &&
			DropPosition.Y >= ContainerTopLeft.Y && DropPosition.Y < ContainerBottomRight.Y)
		{
			return i;
		}
	}

	return INDEX_NONE;
}