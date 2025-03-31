// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_Interactable.h"
#include "LS_BaseItem.generated.h"

UCLASS(config=Game)
class PROJECTLS_API ALS_BaseItem : public AActor, public ILS_Interactable
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	TObjectPtr<UShapeComponent> InteractionCollision;

	TMap<FString, TFunction<void()>> InteractionOptions;



public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;


public:
	ALS_BaseItem();

	virtual UShapeComponent* GetInteractionCollision() const override { return InteractionCollision; };

	virtual TMap<FString, TFunction<void()>> GetInteractionOptions() const override { return InteractionOptions; };

	virtual void ExecuteInteraction(const FText& SelectedOption, APlayerController* PlayerController) override;

	virtual void ShowInteractUI() override;
	virtual void HideInteractUI() override;

#pragma endregion Functions
};

