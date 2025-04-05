// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/LS_BaseItem.h"
#include "LS_SkeletalMeshItem.generated.h"

class USkeletalMeshComponent;

UCLASS()
class PROJECTLS_API ALS_SkeletalMeshItem : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_SkeletalMeshItem();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }

#pragma endregion Functions
};
