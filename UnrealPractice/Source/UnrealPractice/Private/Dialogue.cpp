// Fill out your copyright notice in the Description page of Project Settings.

#include "Dialogue.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueManager.h"
#include "TimerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DialogueWidget.h"


// Sets default values
ADialogue::ADialogue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentIndex = 0;

	lastIndex = 0;

	DialogueManagerInstance = nullptr;

}

// Called when the game starts or when spawned
void ADialogue::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		&ADialogue::FindDialogueManager, 3.0f, false);

	lastIndex = DialogueMessages.Num() - 1;

	
}

// Called every frame
void ADialogue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialogue::StartDialogue()
{
	currentIndex = 0;

	if (DialogueManagerInstance)
	{
		DialogueManagerInstance->SetActiveDialogue(this);
	}

	DisplayCurrentMessage();
}

#pragma region SHOW MESSAGE
void ADialogue::ShowNextMessage()
{
	currentIndex++;

	DisplayCurrentMessage();
}


void ADialogue::DisplayCurrentMessage() 
{
	//Check if the node value is valid
	if (DialogueMessages.IsValidIndex(currentIndex) && DialogueManagerInstance)
	{
		const FDialogueNode& Node = DialogueMessages[currentIndex];
		DialogueManagerInstance->PassDialogueData(Node);

	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Last message was shown!"));
	}
}

bool ADialogue::IsLastMessageShown()
{
	return currentIndex >= lastIndex;
}

#pragma endregion

void ADialogue::FindDialogueManager()
{
	DialogueManagerInstance = Cast<ADialogueManager>
		(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));

	if (!DialogueManagerInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueManager not found!"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueManager found!"));

		//Temporarily starting the dialogue as soon as its found,
		//This will later be covered through another trigger element like NPC or box trigger
		StartDialogue();
	}
}
