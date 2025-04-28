#include "LS_ItemWidget.h"
#include "LS_BaseItem.h"
#include "LS_ItemDragDropOperation.h"
#include "LS_EquipmentSlotWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void ULS_ItemWidget::UpdateSlot(ALS_BaseItem* NewItem)
{
	ItemRef = NewItem;

	if (ItemRef)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULS_ItemWidget::ClearSlot()
{
	UpdateSlot(nullptr);
}

void ULS_ItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (BorderFrame)
	{
		BorderFrame->SetBrushColor(HoveredColor);
	}
}

void ULS_ItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (BorderFrame)
	{
		BorderFrame->SetBrushColor(NormalColor);
	}
}

void ULS_ItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (ItemRef)
	{
		auto DragOp = NewObject<ULS_ItemDragDropOperation>();
		DragOp->DraggedItem = ItemRef;
		DragOp->SourceWidget = this;
		DragOp->DefaultDragVisual = this; // 아이콘 위젯 등으로 대체 가능
		OutOperation = DragOp;
	}
}

bool ULS_ItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto DragOp = Cast<ULS_ItemDragDropOperation>(InOperation);
	if (DragOp && DragOp->DraggedItem)
	{
		if (ItemRef == nullptr)
		{
			// 빈 슬롯에 받기
			ItemRef = DragOp->DraggedItem;

			// 원래 슬롯 비우기
			if (auto SourceSlot = Cast<ULS_ItemWidget>(DragOp->SourceWidget))
			{
				SourceSlot->ClearSlot();
			}
			else if (auto EquipSlot = Cast<ULS_EquipmentSlotWidget>(DragOp->SourceWidget))
			{
				EquipSlot->ClearSlot();
			}

			UpdateSlot(ItemRef);
			return true;
		}
	}
	return false;
}