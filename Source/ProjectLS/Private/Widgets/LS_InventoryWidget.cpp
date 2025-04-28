#include "LS_InventoryWidget.h"
#include "LS_InventoryComponent.h"
#include "LS_InventorySlotWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void ULS_InventoryWidget::SetInventoryComponent(ULS_InventoryComponent* NewComponent)
{
	InventoryComponent = NewComponent;
	RefreshInventory();
}

void ULS_InventoryWidget::RefreshInventory()
{
	if (!InventoryComponent || !InventorySlotWidgetClass || !CanvasPanel)
	{
		return;
	}

	CanvasPanel->ClearChildren();

	for (const FLS_InventoryContainer& Container : InventoryComponent->GetInventoryContainers())
	{
		const float ContainerOffsetX = ContainerPadding * (Container.GridOffset.X > 0 ? 1 : 0);
		const float ContainerOffsetY = ContainerPadding * (Container.GridOffset.Y > 0 ? 1 : 0);
		const float OffsetX = (SlotSize + SlotPadding + ContainerOffsetX) * Container.GridOffset.X;
		const float OffsetY = (SlotSize + SlotPadding + ContainerOffsetY) * Container.GridOffset.Y;

		for (int32 y = 0; y < Container.GridSize.Y; y++)
		{
			for (int32 x = 0; x < Container.GridSize.X; x++)
			{
				int32 Index = Container.GetIndex({ x, y });

				if (Container.InventorySlots.IsValidIndex(Index))
				{
					ULS_InventorySlotWidget* SlotWidget = CreateWidget<ULS_InventorySlotWidget>(this, InventorySlotWidgetClass);
					if (SlotWidget)
					{
						SlotWidget->SetSlotData(Container.InventorySlots[Index]);
						CanvasPanel->AddChild(SlotWidget);

						if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SlotWidget->Slot))
						{
							const float PosX = OffsetX + (SlotSize + SlotPadding) * x;
							const float PosY = OffsetY + (SlotSize + SlotPadding) * y;

							UE_LOG(LogTemp, Log, TEXT("Pos (%f, %f), ContainerOffset (%f, %f)"), PosX, PosY, ContainerOffsetX, ContainerOffsetY);

							CanvasSlot->SetPosition(FVector2D(PosX, PosY));
							CanvasSlot->SetSize(FVector2D(SlotSize, SlotSize));
						}
					}
				}
			}
		}
	}
}