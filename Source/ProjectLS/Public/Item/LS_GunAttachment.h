// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseAttachment.h"
#include "LS_GunAttachment.generated.h"

UCLASS()
class PROJECTLS_API ALS_GunAttachment : public ALS_BaseAttachment
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
	ALS_GunAttachment();

#pragma endregion Functions

};
