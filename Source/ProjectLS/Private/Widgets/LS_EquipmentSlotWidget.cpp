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
		// 아이템이 없으면 기본 빈 아이콘으로 설정
		if (DefaultEmptyIcon)
		{
			ItemIcon->SetBrushFromTexture(DefaultEmptyIcon);
		}
		else
		{
			ItemIcon->SetBrush(FSlateBrush()); // 비우기
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
			// 빈 슬롯에 받기
			ItemRef = DragOp->DraggedItem;

			// 원래 슬롯 비우기
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