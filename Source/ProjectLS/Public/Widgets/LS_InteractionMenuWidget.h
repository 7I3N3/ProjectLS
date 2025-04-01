#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InteractionMenuWidget.generated.h"

class UVerticalBox;
class UTextBlock;

UCLASS()
class PROJECTLS_API ULS_InteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> OptionList;

	UPROPERTY()
	TArray<TObjectPtr<UTextBlock>> OptionTextBlocks;

	TArray<FString> OptionStrings;

	int32 SelectedIndex = 0;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	void RefreshUI();

public:
	UFUNCTION(BlueprintCallable)
	void UpdateMenu(const TArray<FString>& Options);

	UFUNCTION(BlueprintCallable)
	FString GetSelectedOptionString() const;

	UFUNCTION(BlueprintCallable)
	void MoveSelection(int32 Direction);

	FORCEINLINE UVerticalBox* GetOptionList() { return OptionList; }
	FORCEINLINE TArray<UTextBlock*> GetOptionTextBlocks() { return OptionTextBlocks; }

#pragma endregion Functions
};