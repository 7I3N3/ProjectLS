// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInputComponent.h"
#include "LookInputComponent.generated.h"

struct FInputActionValue;
class UEnhancedInputComponent;
class UInputAction;

UCLASS(ClassGroup = (InputModule), meta = (BlueprintSpawnableComponent))
class INPUTMODULE_API ULookInputComponent : public UBaseInputComponent
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
	ULookInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) override;
	void Look(const FInputActionValue& Value);

#pragma endregion Functions
};
