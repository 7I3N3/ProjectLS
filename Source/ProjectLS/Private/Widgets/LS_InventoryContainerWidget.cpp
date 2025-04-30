#include "LS_InventoryContainerWidget.h"
#include "LS_InventorySlotWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void ULS_InventoryContainerWidget::InitializeContainerWidget(int32 InContainerIndex, const FIntPoint GridSize, const float SlotSize)
{
	ContainerIndex = InContainerIndex;

	for (int32 x = 0; x < GridSize.X; x++)
	{
		for (int32 y = 0; y < GridSize.Y; y++)
		{
			FIntPoint LocalGrid = FIntPoint(x, y);
			FVector2D Pos = FVector2D(LocalGrid) * SlotSize;

			ULS_InventorySlotWidget* SlotWidget = CreateWidget<ULS_InventorySlotWidget>(this, SlotWidgetClass);

			SlotCanvas->AddChild(SlotWidget);
			SlotWidget->SetSlotCoordinate(LocalGrid);

			if (UCanvasPanelSlot* InventorySlotSlot = Cast<UCanvasPanelSlot>(SlotWidget->Slot))
			{
				InventorySlotSlot->SetAnchors(FAnchors(0.f, 0.f));
				InventorySlotSlot->SetAlignment(FVector2D(0.f, 0.f));

				InventorySlotSlot->SetSize(FVector2D(SlotSize, SlotSize));
				InventorySlotSlot->SetPosition(Pos);
			}
			SlotWidgets.Add(SlotWidget);
		}
	}
}