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

	//Will point to the options container inside Dialog Instance
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* OptionsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<UUIDialogOption> DialogOptionWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TArray<UUIDialogOption*> DialogOptions;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	UUIDialogOption* DialogOptionInstance;

protected:

	const int32 OptionsCount = 3;

public:
	void HideDialog();
	void ShowDialog();
	
};
