#include "LS_InteractionOptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void ULS_InteractionOptionWidget::SetupOptionWidget(FString OptionString)
{
    if (OptionTextBlock)
    {
        OptionTextBlock->SetText(FText::FromString(OptionString));
    }
}

void ULS_InteractionOptionWidget::SetHighlight(bool bEnabled)
{
    if (HighlightBorder)
    {
        HighlightBorder->SetBrushColor(bEnabled ? FLinearColor(1, 1, 1, 1) : FLinearColor(0, 0, 0, 1));
    }
}