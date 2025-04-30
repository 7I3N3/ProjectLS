#include "LS_InventorySlotWidget.h"
#include "Components/CanvasPanelSlot.h"

void ULS_InventorySlotWidget::SetSlotData(const FLS_InventorySlot& NewSlotData)
{
	SlotData = NewSlotData;
}

void ULS_InventorySlotWidget::SetSlotCoordinate(FIntPoint InCoord)
{
	SlotCoordinate = InCoord;
}
