#include "LS_PlayerEquipmentWidget.h"
#include "LS_EquipmentSlotWidget.h"
#include "Components/Overlay.h"

void ULS_PlayerEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotMap.Empty();

	if (EquipmentSlotContainer)
	{
		TArray<UWidget*> Children = EquipmentSlotContainer->GetAllChildren();
		for (UWidget* Child : Children)
		{
			if (ULS_EquipmentSlotWidget* EquipmentSlot = Cast<ULS_EquipmentSlotWidget>(Child))
			{
				SlotMap.Add(EquipmentSlot->GetSlotType(), EquipmentSlot);
			}
		}
	}
}

void ULS_PlayerEquipmentWidget::UpdateEquipmentSlot(EEquipmentSlotType SlotType, UObject* Item)
{
	if (ULS_EquipmentSlotWidget** FoundWidget = SlotMap.Find(SlotType))
	{
		if (*FoundWidget)
		{
			(*FoundWidget)->SetItem(Item);
		}
	}
}