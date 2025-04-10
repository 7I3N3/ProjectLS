#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_Attachable.h"
#include "LS_BaseBullet.h"
#include "LS_BaseMag.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECTLS_API ALS_BaseMag : public ALS_BaseItem, public ILS_Attachable
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	EAttachmentSlotType AttachmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mag", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ALS_BaseBullet>> AvailableBulletClasses;

	TArray<TSubclassOf<ALS_BaseBullet>> AmmoStack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mag", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmoCount = 30;

	bool bIsAttached = false;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseMag();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	virtual TSubclassOf<ALS_BaseBullet> ConsumeBullet();
	virtual bool LoadAmmo(TSubclassOf<ALS_BaseBullet> Bullet);

	virtual void OnAttached(AActor* Parent, FName SocketName) override;
	virtual void OnDetached() override;

	virtual bool IsAttached() const override { return bIsAttached; }

	FORCEINLINE virtual bool IsEmpty() const { return AmmoStack.IsEmpty(); }
	FORCEINLINE virtual bool IsFull() const { return AmmoStack.Num() == MaxAmmoCount; }

	FORCEINLINE virtual EAttachmentSlotType GetAttachmentSlotType() const override { return AttachmentSlotType; }
	FORCEINLINE TArray<TSubclassOf<ALS_BaseBullet>> GetAvailableBulletClasses() const { return AvailableBulletClasses; }
	FORCEINLINE TArray<TSubclassOf<ALS_BaseBullet>> GetAmmoStack() const { return AmmoStack; }

#pragma endregion Functions
};
