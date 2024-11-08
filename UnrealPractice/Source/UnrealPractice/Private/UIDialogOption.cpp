
// Fill out your copyright notice in the Description page of Project Settings.
#include "UIDialogOption.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUIDialogOption::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UUIDialogOption::OnDialogueSelectedHandler);
	}
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

