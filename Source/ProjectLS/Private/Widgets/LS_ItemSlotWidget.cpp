#include "LS_ItemSlotWidget.h"
#include "LS_BaseItem.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULS_ItemSlotWidget::SetItem(ALS_BaseItem* NewItem)
{
	ItemRef = NewItem;

	if (ItemRef)
	{
		ItemNameText->SetText(FText::FromName(ItemRef->GetItemName()));
		// ������ �������� �������� �ý����� �ִٸ� �̹��� ������ ����
		// ItemIcon->SetBrushFromTexture(ItemRef->GetIcon());
	}
}