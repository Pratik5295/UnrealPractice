// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

void AGameHUD::BeginPlay()
{

	Super::BeginPlay();

	DialogInstance = CreateWidget<UDialogueWidget>(GetWorld(), WidgetClass);

	if (DialogInstance)
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
					OptionsContainer->AddChild(DialogOptionInstance);

					DialogInstance->SetupDialogOptions(DialogOptionInstance);

					DialogOptions.Add(DialogOptionInstance);
				}
			}
		}
	}
}

void AGameHUD::HideDialog() 
{
	if (!DialogInstance) return;

	DialogInstance->SetVisibility(ESlateVisibility::Hidden);
}

void AGameHUD::ShowDialog() 
{
	if (!DialogInstance) return;

	DialogInstance->SetVisibility(ESlateVisibility::Visible);
}
