#pragma once

#include "CoreMinimal.h"
#include "LS_BaseItem.h"
#include "LS_BaseBullet.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECTLS_API ALS_BaseBullet : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:


public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_BaseBullet();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

#pragma endregion Functions
};
