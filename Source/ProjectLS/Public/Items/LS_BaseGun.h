// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_SkeletalMeshItem.h"
#include "LS_Attachable.h"
#include "LS_BaseGun.generated.h"

class USkeletalMeshComponent;
class ILS_Attachable;

USTRUCT(Atomic, BlueprintType)
struct FAttachmentSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
	EAttachmentSlotType SlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
	FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
	TScriptInterface<ILS_Attachable> Attachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment", meta = (MakeEditWidget))
	FTransform SlotTransform;
};

UCLASS()
class PROJECTLS_API ALS_BaseGun : public ALS_SkeletalMeshItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TArray<FAttachmentSlot> Attachments;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseGun();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Take();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Equip();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Examine();

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	virtual bool AttachAttachment(EAttachmentSlotType SlotType, FName SlotName, TScriptInterface<ILS_Attachable> NewAttachment);

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	virtual bool DetachAttachment(EAttachmentSlotType SlotType, FName SlotName);

#pragma endregion Functions
};
