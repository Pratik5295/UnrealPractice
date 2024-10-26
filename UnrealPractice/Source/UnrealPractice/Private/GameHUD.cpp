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
	}
}
