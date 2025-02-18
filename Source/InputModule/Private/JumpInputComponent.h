// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInputComponent.h"
#include "JumpInputComponent.generated.h"

struct FInputActionValue;
class UEnhancedInputComponent;

UCLASS(ClassGroup = (InputModule), meta = (BlueprintSpawnableComponent))
class INPUTMODULE_API UJumpInputComponent : public UBaseInputComponent
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
	UJumpInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) override;

	void Jump();
	void StopJumping();

#pragma endregion Functions
};
