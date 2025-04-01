#include "LS_InteractionMenuWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

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

    OptionList->ClearChildren();
    OptionTextBlocks.Empty();

    for (int32 i = 0; i < OptionStrings.Num(); i++)
    {
        UTextBlock* OptionText = NewObject<UTextBlock>(this);
        OptionText->SetText(FText::FromString(OptionStrings[i]));

        if (i == SelectedIndex)
        {
            OptionText->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
        }
        else
        {
            OptionText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
        }

        OptionList->AddChild(OptionText);
        OptionTextBlocks.Add(OptionText);
    }
}