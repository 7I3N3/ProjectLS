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

void ULS_InventorySlotWidget::SetPositionInCanvas(FVector2D Position)
{
    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot))
    {
        CanvasSlot->SetPosition(Position);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetPositionInCanvas failed: Not inside CanvasPanel"));
    }
}