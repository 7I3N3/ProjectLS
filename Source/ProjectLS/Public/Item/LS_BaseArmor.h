// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseArmor.generated.h"

UCLASS()
class PROJECTLS_API ALS_BaseArmor : public ALS_BaseItem
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
	virtual void Tick(float DeltaTime) override;

public:
	ALS_BaseArmor();

#pragma endregion Functions

};
