// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMenu.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APracticePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPRACTICE_API AAPracticePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	TSubclassOf<class UGameMenu> GameMenuClass;
	
};
