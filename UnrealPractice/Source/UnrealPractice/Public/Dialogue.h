// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueNode.h"
#include "DialogueWidget.h"
#include "GameFramework/Actor.h"
#include "Dialogue.generated.h"

//Forward declare the classes
class ADialogueManager;

UCLASS()
class UNREALPRACTICE_API ADialogue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogue();

	UPROPERTY(BlueprintReadOnly,Category = "Dialogue")
	int currentIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueNode> DialogueMessages;

	ADialogueManager* DialogueManagerInstance;

	FTimerHandle TimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowNextMessage();

	void StartDialogue();


private:
	void DisplayCurrentMessage();
	void FindDialogueManager();

};
