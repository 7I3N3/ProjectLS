#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_Equipable.h"
#include "LS_EquipmentSlotWidget.generated.h"

class UImage;
class UBorder;
class UTexture2D;

UCLASS()
class PROJECTLS_API ULS_EquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentSlot")
	UTexture2D* DefaultEmptyIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentSlot")
	EEquipmentSlotType SlotType;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetItem(UObject* ItemObject);

	FORCEINLINE EEquipmentSlotType GetSlotType() const { return SlotType; }

#pragma endregion Functions
};