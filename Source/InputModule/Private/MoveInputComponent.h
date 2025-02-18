// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInputComponent.h"
#include "MoveInputComponent.generated.h"

struct FInputActionValue;
class UEnhancedInputComponent;

UCLASS(ClassGroup = (InputModule), meta = (BlueprintSpawnableComponent))
class INPUTMODULE_API UMoveInputComponent : public UBaseInputComponent
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
	UMoveInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) override;

	void Move(const FInputActionValue& Value);

#pragma endregion Functions
};
