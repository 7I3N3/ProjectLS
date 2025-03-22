// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseGun.generated.h"

class ALS_BaseBullet;
class ALS_GunAttachment;

UCLASS()
class PROJECTLS_API ALS_BaseGun : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ALS_BaseBullet>> AvailableBullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultMuzzleLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	TMap<FName, ALS_GunAttachment*> Attachments;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ALS_BaseGun();

	UFUNCTION(BlueprintCallable)
	void AddAttachment(ALS_GunAttachment* Attachment);
	UFUNCTION(BlueprintCallable)
	void RemoveAttachment(FName AttachmentSlot);

	bool Fire();

	virtual void Interact(AActor* Interactor) override;
	virtual void ShowInteractionUI() override;
	virtual void HideInteractionUI() override;

	ALS_GunAttachment* GetAttachment(FName AttachmentSlot) const;

	FORCEINLINE TArray<TSubclassOf<ALS_BaseBullet>> GetAvailableBullets() { return AvailableBullets; }

	FTransform GetMuzzleTransform() const;

#pragma endregion Functions

};
