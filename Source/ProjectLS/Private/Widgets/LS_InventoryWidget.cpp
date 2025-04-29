#include "LS_InventoryWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_ItemWidget.h"
#include "LS_InventorySlotWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/WidgetTree.h"

void ULS_InventoryWidget::InitializeInventory(ULS_InventoryComponent* NewComponent)
{
	InventoryComponent = NewComponent;

	if (!InventoryComponent || !SlotWidgetClass) return;

	InventoryCanvas->ClearChildren();
	SlotWidgets.Empty();

	const TArray<FLS_InventoryContainer>& Containers = InventoryComponent->GetContainers();

	for (int32 Index = 0; Index < Containers.Num(); Index++)
	{
		const FIntPoint Offset = Containers[Index].GridOffset;
		const FIntPoint Size = Containers[Index].GridSize;

		UBorder* ContainerBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		ContainerBorder->SetBrushColor(FLinearColor::Black);
		ContainerBorder->SetPadding(FMargin(0));

		UCanvasPanel* ContainerCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
		ContainerBorder->SetContent(ContainerCanvas);
		ContainerBorder->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.2f));

		for (int32 y = 0; y < Size.Y; y++)
		{
			for (int32 x = 0; x < Size.X; x++)
			{
				FIntPoint LocalGrid = FIntPoint(x, y);
				FVector2D Pos = LocalGrid * SlotSize;

				ULS_InventorySlotWidget* SlotWidget = CreateWidget<ULS_InventorySlotWidget>(this, SlotWidgetClass);
				
				SlotWidget->SetPositionInCanvas(Pos);
				SlotWidget->SetSlotCoordinate(LocalGrid);

				SlotWidget->SetContainerIndex(Index);

				ContainerCanvas->AddChild(SlotWidget);
				SlotWidgets.Add(SlotWidget);
			}
		}

		UCanvasPanelSlot* ContainerBorderSlot = InventoryCanvas->AddChildToCanvas(ContainerBorder);
		ContainerBorderSlot->SetPosition(FVector2D(Offset) * SlotSize);
		ContainerBorderSlot->SetSize(FVector2D(Size) * SlotSize);
	}
}

void ULS_InventoryWidget::RefreshInventory()
{
	if (!InventoryComponent || !ItemWidgetClass) return;

	ItemCanvas->ClearChildren();

	const TArray<FLS_InventoryContainer>& Containers = InventoryComponent->GetContainers();

	for (const FLS_InventoryContainer& Container : Containers)
	{
		for (int32 Index = 0; Index < Container.InventorySlots.Num(); ++Index)
		{
			const FLS_InventorySlot& InventorySlot = Container.InventorySlots[Index];

			if (InventorySlot.OccupyingItem && Container.IsRootSlot(Index))
			{
				ALS_BaseItem* Item = InventorySlot.OccupyingItem;
				FIntPoint GridSize = Item->GetItemSize();

				ULS_ItemWidget* NewWidget = CreateWidget<ULS_ItemWidget>(this, ItemWidgetClass);
				NewWidget->SetItem(Item);

				FIntPoint RootCoord = Container.GetSlotWorldPosition(Index);
				PositionItemWidget(NewWidget, RootCoord);

				ItemCanvas->AddChild(NewWidget);
			}
		}
	}
}

void ULS_InventoryWidget::PositionItemWidget(ULS_ItemWidget* ItemWidget, FIntPoint RootSlotCoord)
{
	if (!ItemWidget) return;

	FVector2D CanvasPos = FVector2D(RootSlotCoord.X * SlotSize, RootSlotCoord.Y * SlotSize);
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ItemWidget->Slot);
	if (CanvasSlot)
	{
		CanvasSlot->SetPosition(CanvasPos);
	}
}

void ULS_InventoryWidget::HandleItemDrop(ULS_ItemWidget* DraggedItemWidget, const FVector2D DropPosition)
{
	if (!DraggedItemWidget || !InventoryComponent) return;

	ULS_InventorySlotWidget* TargetSlot = nullptr;

	for (ULS_InventorySlotWidget* InventorySlot : SlotWidgets)
	{
		if (InventorySlot && InventorySlot->IsHovered())
		{
			TargetSlot = InventorySlot;
			break;
		}
	}

	if (TargetSlot)
	{
		const int32 GridX = FMath::FloorToInt(DropPosition.X / SlotSize);
		const int32 GridY = FMath::FloorToInt(DropPosition.Y / SlotSize);

		const int32 ContainerIndex = TargetSlot->GetContainerIndex();

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
					UE_LOG(LogTemp, Log, TEXT("Inventory (%d, %d): %s"), x, y, *Container.InventorySlots[Index].OccupyingItem->GetName());
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