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
		// 아이템 아이콘을 가져오는 시스템이 있다면 이미지 설정도 가능
		// ItemIcon->SetBrushFromTexture(ItemRef->GetIcon());
	}
}