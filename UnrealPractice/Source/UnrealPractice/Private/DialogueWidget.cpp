// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDialogueWidget::SetSpeakerText(const FString& Text)
{
	if (SpeakerName)
	{
		SpeakerName->SetText(FText::FromString(Text));
	}
}

void UDialogueWidget::SetMessageText(const FString& Text)
{
	if (MessageText)
	{
		MessageText->SetText(FText::FromString(Text));
	}
}

void UDialogueWidget::OnNextButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Next button was clicked! Show next message"));
}

void UDialogueWidget::NativeConstruct() 
{
	Super::NativeConstruct();

	if (SpeakerNameValue.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Speaker Name text value is empty, failed to update UI"));
	}
	else
	{
		SetSpeakerText(SpeakerNameValue);
	}

	if (MessageContent.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue Message can not be empty!"));
	}
	else
	{
		SetMessageText(MessageContent);
	}

	if (NextButton)
	{
		NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Next button does not exist"));
	}
}

