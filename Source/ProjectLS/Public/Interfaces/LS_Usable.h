// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LS_Character.h"
#include "LS_Usable.generated.h"

// 이건 꼭 있어야 합니다
UINTERFACE(MinimalAPI)
class ULS_Usable : public UInterface
{
    GENERATED_BODY()
};

class PROJECTLS_API ILS_Usable
{
    GENERATED_BODY()

#pragma region Functions
private:


protected:


public:
    virtual bool CanUse() const = 0;

    virtual void Use(ALS_Character* User) = 0;

    virtual float GetDurability() const = 0;

    virtual float GetMaxDurability() const = 0;

    virtual float GetDurabilityRatio() const
    {
        float Max = GetMaxDurability();
        return Max > 0 ? GetDurability() / Max : 0.0f;
    }

    virtual void RestoreDurability(float Amount) = 0;

#pragma endregion Functions
};