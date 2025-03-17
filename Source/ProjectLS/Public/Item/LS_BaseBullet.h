// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTLS_API ALS_BaseBullet : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	float Penetration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	ALS_BaseBullet();

	void FireInDirection(const FVector& Direction);

	FORCEINLINE float GetDamage() { return Damage; }
	FORCEINLINE float GetPenetration() { return Penetration; }
	FORCEINLINE float GetSpeed() { return Speed; }
	FORCEINLINE USphereComponent* GetCollision() { return CollisionComponent; }
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }

#pragma endregion Functions

};
