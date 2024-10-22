// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPRACTICE_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

	//All public functions declared here
public:
	
	virtual void NativeConstruct() override;	//Overriding the Construct node?

	UFUNCTION(BlueprintCallable)
	void OnStartClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitClicked();
};
