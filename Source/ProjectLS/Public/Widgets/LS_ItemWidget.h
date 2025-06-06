#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_ItemWidget.generated.h"

class UImage;
class UTextBlock;
class UBorder;
class ALS_BaseItem;

UCLASS()
class PROJECTLS_API ULS_ItemWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BorderFrame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TObjectPtr<ALS_BaseItem> ItemRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (AllowPrivateAccess = "true"))
	FLinearColor NormalColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (AllowPrivateAccess = "true"))
	FLinearColor HoveredColor = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float SlotSize = 75.0f;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeItemWidget(ALS_BaseItem* NewItem);

	UFUNCTION(BlueprintPure)
	ALS_BaseItem* GetItem() const { return ItemRef; }

#pragma endregion Functions
};