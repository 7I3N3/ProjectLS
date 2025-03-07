// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInputComponent.h"
#include "InteractInputComponent.generated.h"

struct FInputActionValue;
class UEnhancedInputComponent;

UCLASS(ClassGroup = (InputModule), meta = (BlueprintSpawnableComponent))
class INPUTMODULE_API UInteractInputComponent : public UBaseInputComponent
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:


public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	UInteractInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) override;

	void Interact();
	void StopInteract();

#pragma endregion Functions
};
