#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InteractionMenuWidget.generated.h"

class UImage;
class UVerticalBox;
class UTextBlock;
class ULS_InteractionOptionWidget;

UCLASS()
class PROJECTLS_API ULS_InteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> OptionList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULS_InteractionOptionWidget> OptionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	int32 MaxOptionCount = 5;

	UPROPERTY()
	TArray<TObjectPtr<ULS_InteractionOptionWidget>> OptionWidgets;

	TArray<FString> OptionStrings;

	int32 SelectedIndex = 0;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	void RefreshUI();

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateMenu(const TArray<FString>& Options);

	UFUNCTION(BlueprintCallable)
	FString GetSelectedOptionString() const;

	UFUNCTION(BlueprintCallable)
	void MoveSelection(int32 Direction);

	FORCEINLINE UVerticalBox* GetOptionList() const { return OptionList; }
	FORCEINLINE TArray<ULS_InteractionOptionWidget*> GetOptionTextBlocks() const { return OptionWidgets; }
	FORCEINLINE int32 GetSelectedIndex() const { return SelectedIndex; }

#pragma endregion Functions
};