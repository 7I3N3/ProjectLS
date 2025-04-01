// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LS_Interactable.generated.h"

UINTERFACE(MinimalAPI)
class ULS_Interactable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTLS_API ILS_Interactable
{
	GENERATED_BODY()

#pragma region Functions
private:


protected:


public:
	virtual UShapeComponent* GetInteractionCollision() const = 0;

	virtual TMap<FString, TFunction<void()>> GetInteractionOptions() const = 0;

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) = 0;

#pragma endregion Functions
};
