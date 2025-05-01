#include "LS_InventorySlotWidget.h"
#include "LS_ItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void ULS_InventorySlotWidget::InitializeSlotWidget(const FLS_InventorySlot& NewSlotData, const float SlotSize)
{
	SlotData = NewSlotData;

	if (ItemWidgetClass && ItemCanvas && SlotData.OccupyingItem && SlotData.bIsRoot)
	{
		ItemCanvas->ClearChildren();

		ULS_ItemWidget* ItemWidget = CreateWidget<ULS_ItemWidget>(this, ItemWidgetClass);
		ItemWidget->InitializeItemWidget(SlotData.OccupyingItem);

		ItemCanvas->AddChild(ItemWidget);

		if (UCanvasPanelSlot* ItemWidgetSlot = Cast<UCanvasPanelSlot>(ItemWidget->Slot))
		{
			const FVector2D Size = FVector2D(SlotData.OccupyingItem->GetItemSize()) * SlotSize;

			ItemWidgetSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			ItemWidgetSlot->SetAlignment(FVector2D(0.f, 0.f));

			ItemWidgetSlot->SetPosition(FVector2D(0.f, 0.f));
			ItemWidgetSlot->SetSize(Size);
		}
	}
}

void ULS_InventorySlotWidget::SetSlotCoordinate(FIntPoint InCoord)
{
	SlotCoordinate = InCoord;
}
