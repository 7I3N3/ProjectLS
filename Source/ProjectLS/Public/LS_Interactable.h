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

public:
	virtual void Interact(AActor* Interactor) = 0;
	virtual void ShowInteractionUI() = 0;
	virtual void HideInteractionUI() = 0;
};
