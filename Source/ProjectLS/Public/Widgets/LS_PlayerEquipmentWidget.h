#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_Equipable.h"
#include "LS_PlayerEquipmentWidget.generated.h"

class UOverlay;
class ULS_EquipmentSlotWidget;

UCLASS()
class PROJECTLS_API ULS_PlayerEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> EquipmentSlotContainer;

	TMap<EEquipmentSlotType, ULS_EquipmentSlotWidget*> SlotMap;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void UpdateEquipmentSlot(EEquipmentSlotType SlotType, UObject* Item);

#pragma endregion Functions
};