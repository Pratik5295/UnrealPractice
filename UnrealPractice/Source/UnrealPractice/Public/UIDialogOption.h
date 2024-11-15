// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIDialogOption.generated.h"


UCLASS()
class UNREALPRACTICE_API UUIDialogOption : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OptionMessage;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	int32 NextIndexValue;

	void SetupOption(const FString& _Message, int32 nextIndex);

	UFUNCTION(BlueprintCallable,Category = "Visibility")
	void Hide();

	void Highlighted();

	void UnHighlighted();

protected:

	virtual void NativeConstruct() override;
private:

	void OnDialogueSelectedHandler();
};
