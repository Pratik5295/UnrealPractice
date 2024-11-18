// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FDialogueNode.h"
#include "GameHUD.h"
#include "GameFramework/PlayerController.h"
#include "DialogueManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnConversationDelegate,bool);

// Forward declare the classes
class ADialogue;

UCLASS()
class UNREALPRACTICE_API ADialogueManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADialogueManager();

	APlayerController* PlayerController;
	AGameHUD* hud;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Dialogue")
	ADialogue* activeDialogue;

	FTimerHandle TimerHandle;

	FOnConversationDelegate OnConvoUpdateEvent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetCurrentHUD();

	void PassDialogueData(const FDialogueNode& DialogueNode);

	void SetActiveDialogue(ADialogue* Dialogue);

	UFUNCTION(BlueprintCallable,Category = "Dialgoue")
	void ShowNextMessage();

	UFUNCTION(BlueprintCallable,Category = "Dialogue")
	void ShowDialogHUD();

	UFUNCTION(BlueprintCallable,Category = "Dialogue")
	void ResetDialogHUD();


	void HandlePlayerInput(double moveY);
	void HandlePlayerInteractionInput();


	void TriggerEvent(bool isActive);

};
