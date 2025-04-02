#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InteractionOptionWidget.generated.h"

class UImage;
class UBorder;
class UTextBlock;

UCLASS()
class PROJECTLS_API ULS_InteractionOptionWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UBorder* HighlightBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OptionTextBlock;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:

public:
	UFUNCTION(BlueprintCallable)
	void SetupOptionWidget(FString OptionString);

	UFUNCTION(BlueprintCallable)
	void SetHighlight(bool bEnabled);

	FORCEINLINE UImage* GetBackgroundImage() { return BackgroundImage; }
	FORCEINLINE UTextBlock* GetOptionTextBlock() { return OptionTextBlock; }

#pragma endregion Functions
};