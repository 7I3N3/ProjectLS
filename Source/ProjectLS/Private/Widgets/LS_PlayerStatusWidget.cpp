#include "LS_PlayerStatusWidget.h"
#include "LS_PlayerEquipmentWidget.h"
#include "LS_InventoryWidget.h"
#include "LS_InventoryOwner.h"
#include "LS_BaseItem.h"
#include "Components/ScrollBox.h"

void ULS_PlayerStatusWidget::SetupEquipmentAndInventories(const TMap<EEquipmentSlotType, TScriptInterface<ILS_Equipable>>& EquippedItems)
{
	if (!InventoryScrollBox) return;
	if (!EquipmentWidget) return;

	InventoryScrollBox->ClearChildren();
	Inventories.Empty();

	for (const auto& Pair : EquippedItems)
	{
		ALS_BaseItem* Item = Cast<ALS_BaseItem>(Pair.Value.GetObject());
		EquipmentWidget->UpdateEquipmentSlot(Pair.Key, Item);

		if (!Item || !Item->Implements<ULS_InventoryOwner>()) continue;

		ILS_InventoryOwner* InventoryOwner = Cast<ILS_InventoryOwner>(Item);
		ULS_InventoryComponent* InventoryComponent = InventoryOwner->GetInventoryComponent();

		ULS_InventoryWidget* InventoryWidget = CreateWidget<ULS_InventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			Inventories.Add(InventoryWidget);
			InventoryWidget->InitializeInventory(InventoryComponent);
			InventoryScrollBox->AddChild(InventoryWidget);
		}
	}
}