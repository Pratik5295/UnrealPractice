// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTrigger.h"
#include "Dialogue.h"

// Sets default values
ADialogueTrigger::ADialogueTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	activeDialogue = nullptr;

}

// Called when the game starts or when spawned
void ADialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	FName DialogTag = TEXT("Dialogue");

	UChildActorComponent* DialogueChildActor =
		FindComponentByTag<UChildActorComponent>(DialogTag);

	if (DialogueChildActor)
	{
		activeDialogue = Cast<ADialogue>(DialogueChildActor->GetChildActor());

		if (activeDialogue)
		{
			if (DialogueMessages.Num() > 0) 
			{
				//If nothing is added in parent, then let it show the template dialogue messages
				activeDialogue->SetupDialogueMessages(DialogueMessages);
			}
			UE_LOG(LogTemp, Warning, TEXT("Child found & attached"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Child is not a dialogue"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Child not found"));
	}

}

void ADialogueTrigger::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)  // Ensure the actor is valid and not self
	{
		if (activeDialogue && activeDialogue->currentIndex == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("New Conversation will be started now"));
			//We start the dialogue
			activeDialogue->StartDialogue();
			UE_LOG(LogTemp, Warning, TEXT("Starting new convo"));
		}
	}
}

void ADialogueTrigger::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap End with %s"), *OtherActor->GetName());
	}
}

// Called every frame
void ADialogueTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
