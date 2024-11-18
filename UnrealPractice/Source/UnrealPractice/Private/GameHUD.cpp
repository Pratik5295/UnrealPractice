// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

#include "Components/SizeBox.h"

void AGameHUD::BeginPlay()
{

	Super::BeginPlay();

	DialogInstance = CreateWidget<UDialogueWidget>(GetWorld(), WidgetClass);

	if (DialogInstance) 
	{
		DialogInstance->AddToViewport();
	}
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

void AGameHUD::DialogueNextOption()
{
	if (!DialogInstance) return;

	DialogInstance->SelectNextOption();
}

void AGameHUD::DialoguePreviousOption()
{
	if (!DialogInstance) return;

	DialogInstance->SelectPreviousOption();
}

int32 AGameHUD::GetSelectedDialogOption()
{
	if (!DialogInstance) return 300;

	return DialogInstance->GetSelectedOption();
}
