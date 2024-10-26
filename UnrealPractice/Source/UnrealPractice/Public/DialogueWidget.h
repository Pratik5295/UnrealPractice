// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueNode.h"
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

	//For now let the struct be in public, but will be moved  to private once
	// the system is setup properly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FDialogueNode CurrentNode;

	void SetCurrentNode(const FDialogueNode& NewDialogueNode);
	

protected:

	virtual void NativeConstruct() override;

private:


	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetSpeakerText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetMessageText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnNextButtonClicked();

};