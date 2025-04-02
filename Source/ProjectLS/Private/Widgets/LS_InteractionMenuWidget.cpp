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

    for (int32 i = 0; i < OptionCount; i++)
    {
        ULS_InteractionOptionWidget* OptionWidget = nullptr;

        if (i < CurrentWidgetCount)
        {
            OptionWidget = OptionWidgets[i];
        }
        else
        {
            OptionWidget = CreateWidget<ULS_InteractionOptionWidget>(GetOwningPlayer(), OptionWidgetClass);
            if (!OptionWidget) continue;

            OptionList->AddChild(OptionWidget);
            OptionWidgets.Add(OptionWidget);
        }

        OptionWidget->SetupOptionWidget(OptionStrings[i]);
        OptionWidget->SetHighlight(i == SelectedIndex);
        OptionWidget->SetVisibility(ESlateVisibility::Visible);
    }

    for (int32 i = OptionCount; i < CurrentWidgetCount; i++)
    {
        OptionWidgets[i]->SetVisibility(ESlateVisibility::Collapsed);
    }
}