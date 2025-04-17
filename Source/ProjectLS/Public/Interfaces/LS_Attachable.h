// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LS_Attachable.generated.h"

UENUM(BlueprintType)
enum class EAttachmentSlotType : uint8
{
	AS_Muzzle UMETA(DisplayName = "Muzzle"),
	AS_Foregrip UMETA(DisplayName = "Foregrip"),
	AS_Scope UMETA(DisplayName = "Scope"),
	AS_Tactical UMETA(DisplayName = "Tactical"),
	AS_Mag UMETA(DisplayName = "Mag")
};

UINTERFACE(MinimalAPI)
class ULS_Attachable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTLS_API ILS_Attachable
{
	GENERATED_BODY()

#pragma region Functions
private:


protected:


public:
	virtual EAttachmentSlotType GetAttachmentSlotType() const = 0;

	virtual void OnAttached(AActor* Parent, FName SocketName) = 0;

	virtual void OnDetached() = 0;

	virtual bool IsAttached() const = 0;

#pragma endregion Functions
};

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
};