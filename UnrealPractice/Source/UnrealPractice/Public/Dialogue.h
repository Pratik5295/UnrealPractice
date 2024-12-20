// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueNode.h"
#include "FDialogueOption.h"
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

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Dialogue")
	int currentIndex;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Dialogue")
	int lastIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	TArray<FDialogueNode> DialogueMessages;

	ADialogueManager* DialogueManagerInstance;

	FTimerHandle TimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateDialogueMessage(const FString& Line);

	TArray<FString> ParseCsvLine(const FString& Line);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClearMessages();

	void ShowNextMessage();

	void SelectMessageOption(int32 Selection);

	void SetActiveDialogue();
	void ResetActiveDialogue();

	void StartDialogue();

	bool IsLastMessageShown();

	bool DoesCurrentMessageHaveOptions();

	void SetupDialogueMessages(TArray<FDialogueNode> Messages);

	void AddNewDialogue(const FString& Line);

	void PrintAllMessages();

	void InitializeDialogueMessages();


private:
	void DisplayCurrentMessage();
	void FindDialogueManager();

};
