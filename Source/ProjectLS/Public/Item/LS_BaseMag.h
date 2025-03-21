// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_GunAttachment.h"
#include "LS_BaseMag.generated.h"

class ALS_BaseBullet;

UCLASS()
class PROJECTLS_API ALS_BaseMag : public ALS_GunAttachment
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mag", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ALS_BaseBullet>> AvailableBullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mag", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mag", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ALS_BaseBullet>> AmmoStack;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ALS_BaseMag();

	TSubclassOf<ALS_BaseBullet> ConsumeBullet();			// �߻�
	UFUNCTION(BlueprintCallable)
	bool LoadMag(TSubclassOf<ALS_BaseBullet> Bullet);		// ��ź

	FORCEINLINE TArray<TSubclassOf<ALS_BaseBullet>> GetAvailableBullets() { return AvailableBullets; }
	FORCEINLINE TArray<TSubclassOf<ALS_BaseBullet>> GetAmmoStack() { return AmmoStack; }
	FORCEINLINE int32 GetMaxAmmo() { return MaxAmmo; }
	FORCEINLINE int32 GetCurrentAmmo() { return AmmoStack.Num(); }
	FORCEINLINE bool IsFull() const { return AmmoStack.Num() >= MaxAmmo; }
	FORCEINLINE bool HasAmmo() const { return AmmoStack.Num() > 0 && AmmoStack.Num() <= MaxAmmo; }
	FORCEINLINE bool IsEmpty() const { return AmmoStack.Num() == 0; }

#pragma endregion Functions

};
