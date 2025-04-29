// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_TestItem.generated.h"

class ALS_Character;

UCLASS()
class PROJECTLS_API ALS_TestItem : public ALS_BaseItem
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

	void TakeItem(ALS_Character* Taker);

public:
	ALS_TestItem();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

#pragma endregion Functions
};
