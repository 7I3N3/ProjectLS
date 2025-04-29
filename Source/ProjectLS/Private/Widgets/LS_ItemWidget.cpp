#include "LS_ItemWidget.h"
#include "LS_BaseItem.h"
#include "LS_ItemDragDropOperation.h"
#include "LS_EquipmentSlotWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ULS_ItemWidget::SetItem(ALS_BaseItem* NewItem)
{
	ItemRef = NewItem;

	if (ItemRef)
	{
		ItemIcon->SetBrushFromTexture(ItemRef->GetIcon());

		FVector2D Size = FVector2D(
			ItemRef->GetItemSize().X * SlotSize,
			ItemRef->GetItemSize().Y * SlotSize
		);
		SetDesiredSizeInViewport(Size);
		SetRenderTransformPivot(FVector2D(0.f, 0.f));
	}
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

FReply ULS_ItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		// 메뉴창 띄우기

		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void ULS_ItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	ULS_ItemDragDropOperation* DragOp = NewObject<ULS_ItemDragDropOperation>(this);
	DragOp->Payload = this;
	DragOp->DefaultDragVisual = this;
	DragOp->DraggedItem = ItemRef;

	OutOperation = DragOp;
}

bool ULS_ItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}