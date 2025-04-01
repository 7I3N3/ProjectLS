#pragma once

#include "CoreMinimal.h"
#include "Items/LS_BaseItem.h"
#include "LS_StaticMeshItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECTLS_API ALS_StaticMeshItem : public ALS_BaseItem
{
	GENERATED_BODY()

#pragma region Parameters
private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ItemMesh;

public:


#pragma endregion Parameters

#pragma region Functions
private:


protected:
	virtual void BeginPlay() override;

public:
	ALS_StaticMeshItem();

	virtual void ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController) override;

	FORCEINLINE UStaticMeshComponent* GetItemMesh() const { return ItemMesh; }

#pragma endregion Functions
};
