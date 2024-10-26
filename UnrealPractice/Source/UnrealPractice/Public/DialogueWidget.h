// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPRACTICE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpeakerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextButton;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetSpeakerText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetMessageText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnNextButtonClicked();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dialogue")
	FString SpeakerNameValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dialogue")
	FString MessageContent;


protected:

	virtual void NativeConstruct() override;

};
