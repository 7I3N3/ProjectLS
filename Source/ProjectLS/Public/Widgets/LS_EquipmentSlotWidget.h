#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_Equipable.h"
#include "LS_EquipmentSlotWidget.generated.h"

class UImage;
class UBorder;
class UTexture2D;
class ALS_BaseItem;

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

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TObjectPtr<ALS_BaseItem> ItemRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (AllowPrivateAccess = "true"))
	FLinearColor NormalColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (AllowPrivateAccess = "true"))
	FLinearColor HoveredColor = FLinearColor::Yellow;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSlot(ALS_BaseItem* NewItem);
	UFUNCTION(BlueprintCallable)
	void ClearSlot();

	FORCEINLINE EEquipmentSlotType GetSlotType() const { return SlotType; }

#pragma endregion Functions
};