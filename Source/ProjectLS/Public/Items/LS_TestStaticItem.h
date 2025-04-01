// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/LS_StaticMeshItem.h"
#include "LS_TestStaticItem.generated.h"

UCLASS()
class PROJECTLS_API ALS_TestStaticItem : public ALS_StaticMeshItem
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

	virtual void TestInteractionOptionFunction1();
	virtual void TestInteractionOptionFunction2();
	virtual void TestInteractionOptionFunction3();

public:
	ALS_TestStaticItem();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

#pragma endregion Functions
};
