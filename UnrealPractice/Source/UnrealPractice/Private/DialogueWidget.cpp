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

void UDialogueWidget::SetCurrentNode(const FDialogueNode& NewDialogueNode)
{
	CurrentNode = NewDialogueNode;

	SetSpeakerText(CurrentNode.SpeakerName);
	SetMessageText(CurrentNode.Message);

	bool HasOptions = CurrentNode.HasOptions();

	

	if (!HasOptions)
	{
		for (UUIDialogOption* DialogButton : OptionButtons)
		{
			if (DialogButton)
			{
				DialogButton->Hide();

			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Dialogue Options will be populated soon"));
	}
}

void UDialogueWidget::NativeConstruct() 
{
	Super::NativeConstruct();


	if (NextButton)
	{
		NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Next button does not exist"));
	}

	//Check if struct has meaningful values
	if (!CurrentNode.IsEmpty())
	{
		SetSpeakerText(CurrentNode.SpeakerName);
		SetMessageText(CurrentNode.Message);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Struct of dialogue node is empty"));
	}
}

