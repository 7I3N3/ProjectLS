#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LS_InventoryContainerWidget.generated.h"

class UTextBlock;
class UVerticalBox;

UCLASS()
class PROJECTLS_API ULS_InventoryContainerWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ContainerName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalContainer;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
	

#pragma endregion Functions
};