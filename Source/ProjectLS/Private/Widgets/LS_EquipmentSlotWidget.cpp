#include "LS_EquipmentSlotWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "LS_BaseItem.h"
#include "LS_ItemDragDropOperation.h"
#include "LS_InventorySlotWidget.h"
#include "Engine/Texture2D.h"

void ULS_EquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void ULS_EquipmentSlotWidget::UpdateSlot(ALS_BaseItem* NewItem)
{
	if (!ItemIcon)
		return;

	ItemRef = NewItem;

	if (NewItem)
	{
		UTexture2D* Icon = NewItem->GetIcon();
		if (Icon)
		{
			ItemIcon->SetBrushFromTexture(Icon);
		}
	}
	else
	{
		// �������� ������ �⺻ �� ���������� ����
		if (DefaultEmptyIcon)
		{
			ItemIcon->SetBrushFromTexture(DefaultEmptyIcon);
		}
		else
		{
			ItemIcon->SetBrush(FSlateBrush()); // ����
		}
	}
}

void ULS_EquipmentSlotWidget::ClearSlot()
{
	UpdateSlot(nullptr);
}

void ULS_EquipmentSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (BorderFrame)
	{
		BorderFrame->SetBrushColor(HoveredColor);
	}
}

void ULS_EquipmentSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (BorderFrame)
	{
		BorderFrame->SetBrushColor(NormalColor);
	}
}

void ULS_EquipmentSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (ItemRef)
	{
		auto DragOp = NewObject<ULS_ItemDragDropOperation>();
		DragOp->DraggedItem = ItemRef;
		DragOp->SourceWidget = this;
		DragOp->DefaultDragVisual = this;
		OutOperation = DragOp;
	}
}

bool ULS_EquipmentSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto DragOp = Cast<ULS_ItemDragDropOperation>(InOperation);
	if (DragOp && DragOp->DraggedItem)
	{
		if (ItemRef == nullptr)
		{
			// �� ���Կ� �ޱ�
			ItemRef = DragOp->DraggedItem;

			// ���� ���� ����
			if (auto SourceSlot = Cast<ULS_EquipmentSlotWidget>(DragOp->SourceWidget))
			{
				SourceSlot->ClearSlot();
			}
			else if (auto InventorySlot = Cast<ULS_InventorySlotWidget>(DragOp->SourceWidget))
			{
				//InventorySlot->ClearSlot();
			}

			UpdateSlot(ItemRef);
			return true;
		}
	}
	return false;
}