#include "LS_InteractionMenuWidget.h"
#include "LS_InteractionOptionWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void ULS_InteractionMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    OptionWidgets.Reserve(MaxOptionCount);

    for (int32 i = 0; i < MaxOptionCount; i++)
    {
        ULS_InteractionOptionWidget* OptionWidget = CreateWidget<ULS_InteractionOptionWidget>(GetOwningPlayer(), OptionWidgetClass);
        if (!OptionWidget) continue;

        OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
        OptionWidgets.Add(OptionWidget);
    }
}

void ULS_InteractionMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (OptionList)
    {
        for (ULS_InteractionOptionWidget* OptionWidget : OptionWidgets)
        {
            OptionList->AddChild(OptionWidget);
        }
    }
}

void ULS_InteractionMenuWidget::UpdateMenu(const TArray<FString>& Options)
{
    OptionStrings = Options;
    SelectedIndex = 0;
    RefreshUI();
}

FString ULS_InteractionMenuWidget::GetSelectedOptionString() const
{
    return OptionStrings.IsValidIndex(SelectedIndex) ? OptionStrings[SelectedIndex] : TEXT("");
}

void ULS_InteractionMenuWidget::MoveSelection(int32 Direction)
{
    if (OptionStrings.Num() > 0)
    {
        SelectedIndex = (SelectedIndex + Direction + OptionStrings.Num()) % OptionStrings.Num();
        RefreshUI();
    }
}

void ULS_InteractionMenuWidget::RefreshUI()
{
    if (!OptionList) return;

    int32 OptionCount = OptionStrings.Num();
    int32 CurrentWidgetCount = OptionWidgets.Num();

    while (OptionWidgets.Num() < OptionCount)
    {
        ULS_InteractionOptionWidget* OptionWidget = CreateWidget<ULS_InteractionOptionWidget>(GetOwningPlayer(), OptionWidgetClass);
        if (!OptionWidget) break;

        OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
        OptionList->AddChild(OptionWidget);
        OptionWidgets.Add(OptionWidget);
    }

    for (int32 i = 0; i < OptionWidgets.Num(); i++)
    {
        ULS_InteractionOptionWidget* OptionWidget = OptionWidgets[i];

        if (!OptionWidget) continue;

        if (i < OptionCount)
        {
            OptionWidget->SetupOptionWidget(OptionStrings[i]);
            OptionWidget->SetHighlight(i == SelectedIndex);
            OptionWidget->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}