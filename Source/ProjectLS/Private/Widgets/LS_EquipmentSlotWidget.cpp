#include "LS_EquipmentSlotWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "LS_BaseItem.h"
#include "Engine/Texture2D.h"

void ULS_EquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void ULS_EquipmentSlotWidget::SetItem(UObject* ItemObject)
{
	if (!ItemIcon)
		return;

	if (ItemObject)
	{
		if (ALS_BaseItem* Item = Cast<ALS_BaseItem>(ItemObject))
		{
			UTexture2D* Icon = Item->GetIcon();
			if (Icon)
			{
				ItemIcon->SetBrushFromTexture(Icon);
				return;
			}
		}
	}

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