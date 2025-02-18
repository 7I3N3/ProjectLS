// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LS_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputConfigComponent;
class UMoveInputComponent;
class ULookInputComponent;
class UJumpInputComponent;

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

protected:


public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override; 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	ALS_Character();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UInputConfigComponent* GetInputConfig() const { return InputConfig; }

#pragma endregion Functions
};
