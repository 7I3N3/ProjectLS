// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LS_BaseItem.h"
#include "LS_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputConfigComponent;
class UMoveInputComponent;
class ULookInputComponent;
class UJumpInputComponent;
class UInteractInputComponent;
class UPrimaryAttackInputComponent;
class UAlternativeAttackInputComponent;

class ALS_BaseItem;

class UAbilitySystemComponent;

UCLASS()
class PROJECTLS_API ALS_Character : public ACharacter
{
	GENERATED_BODY()

#pragma region Parameters
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputConfigComponent* InputConfig;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UMoveInputComponent* MoveInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	ULookInputComponent* LookInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UJumpInputComponent* JumpInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInteractInputComponent* InteractInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UPrimaryAttackInputComponent* PrimaryAttackInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UAlternativeAttackInputComponent* AlternativeAttackInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = "true"))
	float InteractDistance = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentInteract;

public:
	

#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override; 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CheckInteract();

public:
	ALS_Character();

	virtual void Tick(float DeltaTime) override;

	void EquipItem(ALS_BaseItem* Item);
	bool IsItemEquipped(EEquipmentSlot Slot) const;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UInputConfigComponent* GetInputConfig() const { return InputConfig; }

	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	FORCEINLINE float GetInteractDistance() const { return InteractDistance; }
	FORCEINLINE AActor* GetCurrentInteract() const { return CurrentInteract; }

#pragma endregion Functions
};
