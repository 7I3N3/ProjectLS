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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float BaseSpeed = 700.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float MinSpeedMultiplier = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float MaxSpeedMultiplier = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float InterpExponent = 2.0f;

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
