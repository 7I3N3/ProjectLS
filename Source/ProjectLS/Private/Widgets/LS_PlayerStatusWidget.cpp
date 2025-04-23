#include "LS_PlayerStatusWidget.h"
#include "LS_PlayerEquipmentWidget.h"
#include "LS_InventoryWidget.h"
#include "LS_InventoryOwner.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void ULS_PlayerStatusWidget::SetupEquipmentAndInventories(const TMap<EEquipmentSlotType, TScriptInterface<ILS_Equipable>>& EquippedItems)
{
	if (!InventoryContainer) return;
	if (!EquipmentWidget) return;

	InventoryContainer->ClearChildren();

	for (const auto& Pair : EquippedItems)
	{
		UObject* ItemObject = Pair.Value.GetObject();
		EquipmentWidget->UpdateEquipmentSlot(Pair.Key, ItemObject);

		if (!ItemObject || !ItemObject->Implements<ULS_InventoryOwner>()) continue;

		ILS_InventoryOwner* InventoryOwner = Cast<ILS_InventoryOwner>(ItemObject);
		TArray<ULS_InventoryComponent*> InventoryComponents = InventoryOwner->GetInventoryComponents();

		if (InventoryComponents.Num() > 0 && InventoryWidgetClass)
		{
			for (auto InventoryComponent : InventoryComponents)
			{
				ULS_InventoryWidget* InventoryWidget = CreateWidget<ULS_InventoryWidget>(this, InventoryWidgetClass);
				if (InventoryWidget)
				{
					InventoryWidget->SetInventoryComponent(InventoryComponent);
					InventoryContainer->AddChildToVerticalBox(InventoryWidget);
				}
			}
		}
	}
}