// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue.h"

// Sets default values
ADialogue::ADialogue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentIndex = 0;

}

// Called when the game starts or when spawned
void ADialogue::BeginPlay()
{
	Super::BeginPlay();

	DisplayCurrentMessage();
	
}

// Called every frame
void ADialogue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogue::DisplayCurrentMessage() 
{
	//Check if the node value is valid
	if (DialogueMessages.IsValidIndex(currentIndex))
	{
		const FDialogueNode& Node = DialogueMessages[currentIndex];

		UE_LOG(LogTemp, Log, TEXT("Speaker: %s"), *Node.SpeakerName);
		UE_LOG(LogTemp, Log, TEXT("Message: %s"), *Node.Message);
	}
}

