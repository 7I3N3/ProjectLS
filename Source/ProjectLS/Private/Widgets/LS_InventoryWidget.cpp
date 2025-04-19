#include "LS_InventoryWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_ItemSlotWidget.h"
#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"

void ULS_InventoryWidget::SetInventoryComponent(ULS_InventoryComponent* NewComponent)
{
	InventoryComponent = NewComponent;
	RefreshGrid();
}

void ULS_InventoryWidget::RefreshGrid()
{
	if (!InventoryComponent || !ItemSlotClass || !GridPanel) return;

	GridPanel->ClearChildren();

	FIntPoint GridSize = InventoryComponent->GetGridSize();

	for (const FItemSlotData& SlotData : InventoryComponent->GetAllItems())
	{
		if (!SlotData.Item) continue;

		ULS_ItemSlotWidget* ItemSlot = CreateWidget<ULS_ItemSlotWidget>(this, ItemSlotClass);
		if (!ItemSlot) continue;

		ItemSlot->SetItem(SlotData.Item);

		int32 X = SlotData.SlotPos.X;
		int32 Y = SlotData.SlotPos.Y;

		GridPanel->AddChildToGrid(ItemSlot, Y, X);
	}
}