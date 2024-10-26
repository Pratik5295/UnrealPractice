// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameHUD.h"
#include "DialogueManager.generated.h"

UCLASS()
class UNREALPRACTICE_API ADialogueManager : public AActor
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ADialogueManager();

	APlayerController* PlayerController;
	AGameHUD* hud;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetCurrentHUD();

	void PassDialogueData(const FDialogueNode& DialogueNode);

	FTimerHandle TimerHandle;

};
