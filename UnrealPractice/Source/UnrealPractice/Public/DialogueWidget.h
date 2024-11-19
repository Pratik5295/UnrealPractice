// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueNode.h"
#include "UIDialogOption.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"


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

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* OptionsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<UUIDialogOption> DialogOptionWidgetClass;

	//For now let the struct be in public, but will be moved  to private once
	// the system is setup properly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FDialogueNode CurrentNode;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	UUIDialogOption* DialogOptionInstance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dialogue")
	TArray<UUIDialogOption*> DialogOptions;


	//Functions
	void SetCurrentNode(const FDialogueNode& NewDialogueNode);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetSpeakerText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetMessageText(const FString& Text);

	void SetupDialogOptions(UUIDialogOption* DialogOption);

	int32 GetSelectedOption();
	void HideDialog();
	void ShowDialog();

	//Showcase different options
	void SelectNextOption();
	void SelectPreviousOption();

protected:

	virtual void NativeConstruct() override;
	const int32 OptionsCount = 3;

private:

	int32 CurrentOptionCount = 0;
	int32 SelectedOption = 0;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnNextButtonClicked();


	//Hide Options
	void HideAllOptions();

	void ShowOptions(const FDialogueNode& DialogueNode,int32 options);

	void HighlightOption();

	void UnHighlightCurrent();


};
