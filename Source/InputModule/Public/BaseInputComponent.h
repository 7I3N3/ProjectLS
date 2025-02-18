// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseInputComponent.generated.h"

class UInputAction;
class UEnhancedInputComponent;

UCLASS( ClassGroup=(InputModule), meta=(BlueprintSpawnableComponent) )
class INPUTMODULE_API UBaseInputComponent : public UActorComponent
{
	GENERATED_BODY()
	
#pragma region Parameters
private:


protected:
	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputAction;

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	UBaseInputComponent();

	virtual void BindInput(UEnhancedInputComponent* InputComponent) PURE_VIRTUAL(UBaseInputComponent::BindInput, );

#pragma endregion Functions
};
