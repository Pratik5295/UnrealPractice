// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"
#include "TimerManager.h"
#include "Dialogue.h"


// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	activeDialogue = nullptr;
	hud = nullptr;

}

// Called when the game starts or when spawned
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		&ADialogueManager::GetCurrentHUD, 1.0f, false);
}

// Called every frame
void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogueManager::GetCurrentHUD()
{
	 PlayerController =
		GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		hud = Cast<AGameHUD>(PlayerController->GetHUD());

		if (hud)
		{
			UE_LOG(LogTemp, Log, TEXT("HUD found!"));
		}
	}
}

void ADialogueManager::SetActiveDialogue(ADialogue* Dialogue)
{
	activeDialogue = Dialogue;

	ShowDialogHUD();
}

void ADialogueManager::ShowNextMessage()
{
	if (activeDialogue)
	{
		if (activeDialogue->IsLastMessageShown())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Not showing you anythign more!!"));
		
			//Hide the widget and set active dialogue to null
			ResetDialogHUD();
		}
		else
		{
			activeDialogue->ShowNextMessage();
		}
	}
}

void ADialogueManager::PassDialogueData(const FDialogueNode& DialogueNode)
{
	if (hud)
	{
		hud->DialogInstance->SetSpeakerText(*DialogueNode.SpeakerName);
		hud->DialogInstance->SetMessageText(*DialogueNode.Message);
	}
}

void ADialogueManager::ShowDialogHUD()
{
	if (hud && activeDialogue)
	{
		hud->ShowDialog();
	}
}

void ADialogueManager::ResetDialogHUD()
{
	activeDialogue = nullptr;

	if (hud)
	{
		hud->HideDialog();
	}

	if (activeDialogue)
	{
		activeDialogue = nullptr;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Dialog HUD should be hidden?"));
}

