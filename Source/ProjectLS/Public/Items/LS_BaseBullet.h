#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseBullet.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTLS_API ALS_BaseBullet : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:
	bool bIsActive = false;

	FVector PreviousLocation;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 3000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float Penetration = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float Bounciness = 0.3f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float Friction = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float Sharpness = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float GravityScale = 1.0f;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseBullet();

	virtual void Tick(float DeltaTime) override;

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;
	
	void Take(ALS_Character* Taker);

	void ActivateBullet(FVector Direction, float Speed);
	void DeactivateBullet();

	bool ShouldRicochet(const FVector& HitNormal, const FVector& BulletDirection) const;

	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion Functions
};
