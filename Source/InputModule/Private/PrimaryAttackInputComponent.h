// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInputComponent.h"
#include "PrimaryAttackInputComponent.generated.h"

class UEnhancedInputComponent;

UCLASS(ClassGroup = (InputModule), meta = (BlueprintSpawnableComponent))
class INPUTMODULE_API UPrimaryAttackInputComponent : public UBaseInputComponent
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
	UPrimaryAttackInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) override;

	void PrimaryAttack();
	void PrimaryAttackStop();

#pragma endregion Functions
};
