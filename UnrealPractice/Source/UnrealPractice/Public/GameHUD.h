// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DialogueWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPRACTICE_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	TSubclassOf<UDialogueWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite,Category = "Dialogue")
	UDialogueWidget* DialogInstance;


public:
	void HideDialog();
	void ShowDialog();
	
};
