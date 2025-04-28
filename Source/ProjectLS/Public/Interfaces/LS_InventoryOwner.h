// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LS_InventoryOwner.generated.h"

class ULS_InventoryComponent;
class ULS_InventoryWidget;

UINTERFACE(MinimalAPI)
class ULS_InventoryOwner : public UInterface
{
    GENERATED_BODY()
};

class PROJECTLS_API ILS_InventoryOwner
{
    GENERATED_BODY()

#pragma region Functions
private:


protected:


public:
    virtual ULS_InventoryComponent* GetInventoryComponent() const = 0;

#pragma endregion Functions
};