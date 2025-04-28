#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "LS_ItemDragDropOperation.generated.h"

class UUserWidget;
class ALS_BaseItem;

UCLASS()
class PROJECTLS_API ULS_ItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ALS_BaseItem> DraggedItem;

	// 드래그를 시작한 슬롯 위젯
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUserWidget> SourceWidget;
};