#include "LS_PlayerStatusWidget.h"
#include "LS_PlayerEquipmentWidget.h"
#include "LS_InventoryWidget.h"
#include "LS_InventoryOwner.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void ULS_PlayerStatusWidget::SetupEquipmentAndInventories(const TMap<EEquipmentSlotType, TScriptInterface<ILS_Equipable>>& EquippedItems)
{
	if (!InventoryContainer) return;
	InventoryContainer->ClearChildren();

	for (const auto& Pair : EquippedItems)
	{
		UObject* ItemObject = Pair.Value.GetObject();
		if (!ItemObject || !ItemObject->Implements<ULS_InventoryOwner>()) continue;

		ILS_InventoryOwner* InventoryOwner = Cast<ILS_InventoryOwner>(ItemObject);
		ULS_InventoryComponent* InvComp = InventoryOwner->GetInventoryComponent();
		TSubclassOf<ULS_InventoryWidget> WidgetClass = InventoryOwner->GetInventoryWidgetClass();

		if (InvComp && WidgetClass)
		{
			ULS_InventoryWidget* InventoryWidget = CreateWidget<ULS_InventoryWidget>(this, WidgetClass);
			if (InventoryWidget)
			{
				InventoryWidget->SetInventoryComponent(InvComp);
				InventoryContainer->AddChildToVerticalBox(InventoryWidget);
			}
		}

		if (EquipmentWidget)
		{
			EquipmentWidget->UpdateEquipmentSlot(Pair.Key, ItemObject);
		}
	}
}