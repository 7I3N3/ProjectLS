// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputConfigComponent.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
class UBaseInputComponent;
class UInputAction;

UCLASS( ClassGroup=(InputModule), meta=(BlueprintSpawnableComponent) )
class INPUTMODULE_API UInputConfigComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Parameters
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	UEnhancedInputComponent* EnhancedInputComponent;

	TMap<UBaseInputComponent*, UInputAction*> InputMappings;

protected:


public:


#pragma endregion Parameters

#pragma region Functions
private:
	UInputAction* FindActionByName(const FName& ActionName);

protected:
	virtual void BeginPlay() override;

public:
	UInputConfigComponent();

	void RegisterInputComponent(UBaseInputComponent* InputComponent);
	void RegisterAllInputComponents();

	void OnControllerChanged();

	void SetupInput(UEnhancedInputComponent* InputComponent);

	void ChangeKeyBinding(UBaseInputComponent* InputComponent, FKey NewKey);

	void SaveKeyBindings();
	void LoadKeyBindings();

#pragma endregion Functions
};
