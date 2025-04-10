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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName ItemName;

	TMap<FString, TFunction<void(ALS_Character* Interactor)>> InteractionOptions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ItemMesh;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseItem();

	virtual TMap<FString, TFunction<void(ALS_Character* Interactor)>> GetInteractionOptions() const override { return InteractionOptions; };

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	FORCEINLINE FName GetItemID() const { return ItemID; }
	FORCEINLINE FName GetItemName() const { return ItemName; }

	FORCEINLINE UStaticMeshComponent* GetItemMesh() const { return ItemMesh; }

#pragma endregion Functions
};

