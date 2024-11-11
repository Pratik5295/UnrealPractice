// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

#include "Components/SizeBox.h"

void AGameHUD::BeginPlay()
{

	Super::BeginPlay();

	DialogInstance = CreateWidget<UDialogueWidget>(GetWorld(), WidgetClass);

	if (DialogInstance) {
		DialogInstance->AddToViewport();
	}
	/*if (DialogInstance)
	{
		DialogInstance->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("Dialog widget has been created"));

		HideDialog();

		OptionsContainer = DialogInstance->OptionsContainer;

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

					DialogInstance->SetupDialogOptions(DialogOptionInstance);

					DialogOptions.Add(DialogOptionInstance);
				}
			}
		}
	}*/
}

void AGameHUD::HideDialog() 
{
	if (!DialogInstance) return;

	DialogInstance->HideDialog();
}

void AGameHUD::ShowDialog() 
{
	if (!DialogInstance) return;

	DialogInstance->ShowDialog();
}
