// Fill out your copyright notice in the Description page of Project Settings.

#include "APracticePlayerController.h"
#include "Blueprint/UserWidget.h"

void AAPracticePlayerController::BeginPlay()
{
	if (GameMenuClass)
	{
		//Given that the value is assigned in blueprint

		UGameMenu* Menu = CreateWidget<UGameMenu>(this, GameMenuClass);

		if (Menu)
		{
			Menu->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}
