// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UIDialogOption.h"


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

void UDialogueWidget::SetupDialogOptions(UUIDialogOption* DialogOption)
{
	DialogOptionInstance = DialogOption;
}

void UDialogueWidget::OnNextButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Next button was clicked! Show next message"));
}

void UDialogueWidget::HideAllOptions()
{
	if (OptionsContainer->GetChildrenCount() > 0)
	{
		for (int i = 0; i < OptionsContainer->GetChildrenCount(); i++)
		{
			OptionsContainer->GetChildAt(i)->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UDialogueWidget::ShowOptions(const FDialogueNode& DialogueNode,int32 options)
{
	if (OptionsContainer->GetChildrenCount() == 0) return;

	TArray<FDialogueOption> Options = DialogueNode.Options;

	for (int i = 0; i < Options.Num(); i++)
	{
		FDialogueOption OptionData = Options[i];

		OptionsContainer->GetChildAt(i)->SetVisibility(ESlateVisibility::Visible);

		UUIDialogOption* Option = Cast<UUIDialogOption>(OptionsContainer->GetChildAt(i));

		if (Option)
		{
			Option->SetupOption(OptionData.OptionMessage, OptionData.NextInteger);
		}
	}
}

void UDialogueWidget::SetCurrentNode(const FDialogueNode& NewDialogueNode)
{
	HideAllOptions();

	CurrentNode = NewDialogueNode;

	SetSpeakerText(CurrentNode.SpeakerName);
	SetMessageText(CurrentNode.Message);

	bool HasOptions = CurrentNode.HasOptions();

	if (HasOptions)
	{
		int32 noOptions = CurrentNode.OptionCount();

		ShowOptions(NewDialogueNode,noOptions);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("This message doesnt have any options to show"));
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
	
		UE_LOG(LogTemp, Log, TEXT("Dialog widget has been created"));

		

		if (OptionsContainer)
		{
			for (int i = 0; i < OptionsCount; i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Options container also exists"));

				DialogOptionInstance = CreateWidget<UUIDialogOption>(GetWorld(), DialogOptionWidgetClass);

				if (DialogOptionInstance)
				{
					UVerticalBoxSlot* BoxSlot = OptionsContainer->AddChildToVerticalBox(DialogOptionInstance);

					if (BoxSlot)
					{
						BoxSlot->SetPadding(FMargin(2.0f));

						BoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						BoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);


						BoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
					}

					DialogOptions.Add(DialogOptionInstance);
				}
			}
		}

		HideDialog();

		
}


	void UDialogueWidget::HideDialog()
	{
		UDialogueWidget::SetVisibility(ESlateVisibility::Hidden);
	}

	void UDialogueWidget::ShowDialog()
	{
		UDialogueWidget::SetVisibility(ESlateVisibility::Visible);
	}

