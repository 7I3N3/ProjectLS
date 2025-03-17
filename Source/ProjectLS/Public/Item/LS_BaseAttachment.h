// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseAttachment.generated.h"

UCLASS()
class PROJECTLS_API ALS_BaseAttachment : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	FName AttachmentSlotName;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ALS_BaseAttachment();

	virtual void AttachToOwner(AActor* OwnerActor);

	FORCEINLINE FName GetSlotName() { return AttachmentSlotName; }

#pragma endregion Functions

};
