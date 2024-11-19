
// Fill out your copyright notice in the Description page of Project Settings.
#include "UIDialogOption.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUIDialogOption::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIDialogOption::OnDialogueSelectedHandler()
{
	UE_LOG(LogTemp, Log, TEXT("Dialogue Option selected"));
}

void UUIDialogOption::SetupOption(const FString& _Message,int32 nextIndex)
{
	OptionMessage->SetText(FText::FromString(_Message));
	NextIndexValue = nextIndex;
}

void UUIDialogOption::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogTemp, Log, TEXT("Hiding: %s,Current Visibility: %d "),
		*GetFName().ToString(),static_cast<int32>(GetVisibility()));
}

/// <summary>
/// The UI option will be highlighted in different color?
/// </summary>
void UUIDialogOption::Highlighted()
{
	OptionMessage->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
}

/// <summary>
/// UI Option will be unhighlighted if it was highlighted
/// </summary>
void UUIDialogOption::UnHighlighted()
{
	OptionMessage->SetColorAndOpacity(FSlateColor(FLinearColor::Black));
}

