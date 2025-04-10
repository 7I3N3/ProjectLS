// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_SkeletalMeshItem.h"
#include "LS_Attachable.h"
#include "LS_Equipable.h"
#include "LS_BaseGun.generated.h"

class USkeletalMeshComponent;
class ALS_Character;

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAuto    UMETA(DisplayName = "Semi-Auto"),   // 단발
	Burst       UMETA(DisplayName = "Burst"),       // 3점사
	FullAuto    UMETA(DisplayName = "Full Auto")    // 연사
};

UCLASS()
class PROJECTLS_API ALS_BaseGun : public ALS_SkeletalMeshItem, public ILS_Equipable
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TArray<FAttachmentSlot> Attachments;

	bool bIsEquipped = false;

	TObjectPtr<ALS_Character> EquippedCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	EEquipmentSlotType EquipmentSlot = EEquipmentSlotType::ES_MainWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 BurstCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	EFireMode SupportedFireModes;

	UPROPERTY(BlueprintReadOnly, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	EFireMode CurrentFireMode = EFireMode::SemiAuto;

	FTimerHandle FireTimerHandle;
	int32 BurstShotsFired = 0;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

	void FireBullet();
	void HandleBurstFire();

public:
	ALS_BaseGun();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	virtual void Equip(ALS_Character* Wearer) override;
	virtual void Unequip(ALS_Character* Wearer) override;

	virtual EEquipmentSlotType GetSlotType() const override { return EquipmentSlot; }
	virtual bool IsEquipped() const override { return bIsEquipped; }
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Take(ALS_Character* Interactor);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Examine(ALS_Character* Interactor);

	UFUNCTION(BlueprintCallable, Category = "Gun")
	void StartFiring();

	UFUNCTION(BlueprintCallable, Category = "Gun")
	void StopFiring();

	UFUNCTION(BlueprintCallable, Category = "Gun")
	void SwitchFireMode();

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	virtual bool AttachAttachment(TScriptInterface<ILS_Attachable> NewAttachment, FName SlotName);

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	virtual bool DetachAttachment(EAttachmentSlotType SlotType, FName SlotName);

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	virtual TScriptInterface<ILS_Attachable> GetAttachment(EAttachmentSlotType SlotType, FName SlotName = TEXT("")) const;

	FVector GetMuzzleLocation() const;
	FRotator GetMuzzleRotation() const;

#pragma endregion Functions
};
