// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InputConfigSave.generated.h"

USTRUCT(BlueprintType)
struct FKeyConfig
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FName ActionName;

    UPROPERTY(BlueprintReadWrite)
    FKey Key;

    FKeyConfig() {}
    FKeyConfig(FName InActionName, FKey InKey)
        : ActionName(InActionName), Key(InKey) {
    }
};

UCLASS()
class INPUTMODULE_API UInputConfigSave : public USaveGame
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:


public:
    UPROPERTY(BlueprintReadWrite)
    TArray<FKeyConfig> KeyBindings;

#pragma endregion Parameters

#pragma region Functions
private:


protected:


public:
    static FString GetSaveSlotName() { return TEXT("InputConfig"); }

#pragma endregion Functions
};
