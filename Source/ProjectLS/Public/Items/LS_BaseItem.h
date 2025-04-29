// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_Interactable.h"
#include "LS_BaseItem.generated.h"

class UTexture2D;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 MaxStackCount = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 CurrentStackCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FIntPoint ItemSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bIsRotated = false;

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

	FORCEINLINE FIntPoint GetItemSize() const { return bIsRotated ? FIntPoint(ItemSize.Y, ItemSize.X) : ItemSize; }

	FORCEINLINE UTexture2D* GetIcon() const { return ItemIcon; }

	FORCEINLINE bool IsFullStack() const { return CurrentStackCount == MaxStackCount; }

	bool CanStackWith(const ALS_BaseItem* Other) const
	{
		return bIsStackable && Other && Other->bIsStackable &&
			GetClass() == Other->GetClass();
	}

	FORCEINLINE int32 GetRemainingStackSpace() const { return MaxStackCount - CurrentStackCount; }

	void AddStack(int32 Amount);

	FORCEINLINE bool IsStackable() const { return bIsStackable; }

	FORCEINLINE int32 GetCurrentStackCount() const { return CurrentStackCount; }
	FORCEINLINE int32 GetMaxStackCount() const { return MaxStackCount; }

	void InventoryRotate() { bIsRotated = !bIsRotated; }
#pragma endregion Functions
};

