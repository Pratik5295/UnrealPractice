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

void ADialogue::ClearMessages() 
{
	if (DialogueMessages.Num() == 0) return;

	DialogueMessages.Empty();
}

#pragma region SHOW MESSAGE
void ADialogue::ShowNextMessage()
{
	const FDialogueNode& Node = DialogueMessages[currentIndex];

	if (Node.HasJump)
	{
		if (Node.NextJump != 99)
		{
			currentIndex = Node.NextJump;
		}
	}
	else 
	{
		currentIndex++;
	}

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
}

void ADialogue::SelectMessageOption(int32 Selected)
{
	if (DialogueMessages.IsValidIndex(currentIndex) && DialogueManagerInstance)
	{
		const FDialogueNode& Node = DialogueMessages[currentIndex];

		int32 nextMessageIndex = Node.GetNextIndexFromOption(Selected);

		currentIndex = nextMessageIndex;

		DisplayCurrentMessage();
	}
}

#pragma endregion

bool ADialogue::IsLastMessageShown()
{
	const FDialogueNode& Node = DialogueMessages[currentIndex];

	bool isLast = false;
	if (Node.NextJump == 99)
	{
		isLast = true;
	}
	else
	{
		isLast = currentIndex >= lastIndex;
	}

	return isLast;
}

bool ADialogue::DoesCurrentMessageHaveOptions()
{
	if (DialogueMessages.Num() == 0) return false;

	const FDialogueNode& Node = DialogueMessages[currentIndex];

	return Node.HasOptions();
}

void ADialogue::SetupDialogueMessages(TArray<FDialogueNode> Messages)
{
	DialogueMessages = Messages;
	InitializeDialogueMessages();
}

void ADialogue::InitializeDialogueMessages()
{
	currentIndex = 0;
	lastIndex = DialogueMessages.Num() - 1;

	UE_LOG(LogTemp, Warning, TEXT("Messages found, Setup Complete"));
}

void ADialogue::PrintAllMessages() 
{
	if (DialogueMessages.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("There are no messages here"));
	}
	else
	{
		for (int32 i = 0; i < DialogueMessages.Num(); i++)
		{
			FString Message = FString::Printf(TEXT("%s,%s"), *DialogueMessages[i].SpeakerName, *DialogueMessages[i].Message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), * Message);
		}
	}
}



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
	}
}


void ADialogue::AddNewDialogue(const FString& Line)
{
	CreateDialogueMessage(Line);
}


void ADialogue::CreateDialogueMessage(const FString& Line)
{
	TArray<FString> Columns = ParseCsvLine(Line);

	FDialogueNode DialogueNode;
	DialogueNode.SpeakerName = Columns[1];
	DialogueNode.Message = Columns[2];

	FString jump = Columns[3];
	bool allowJump = false;
	int32 nextIndex = 0;

	if (!jump.IsEmpty())
	{
		//No options, jump to next node
		allowJump = true;
		nextIndex = FCString::Atoi(*jump);

		DialogueNode.HasJump = allowJump;
		DialogueNode.NextJump = nextIndex;
	}
	else 
	{
		//Has Options

		int32 counterIndex = 4;
		if (counterIndex < Columns.Num())
		{
			for (; counterIndex < Columns.Num(); counterIndex += 2)
			{
				if (counterIndex + 1 < Columns.Num())
				{
					FDialogueOption Option;
					Option.OptionMessage = Columns[counterIndex];
					Option.NextInteger = FCString::Atoi(*Columns[counterIndex + 1]);

					DialogueNode.AddOption(Option);
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Line Added!"));

	DialogueMessages.Add(DialogueNode);
}

TArray<FString> ADialogue::ParseCsvLine(const FString& Line)
{
	TArray<FString> Result;

	bool InQuotes = false;
	FString Value;

	for (int32 i = 0; i < Line.Len(); i++)
	{
		TCHAR Char = Line[i];

		if (Char == TEXT('"'))
		{
			InQuotes = !InQuotes;
			continue;
		}

		if (Char == TEXT(',') && !InQuotes)
		{
			Result.Add(Value);
			Value.Empty();
			continue;
		}

		Value.AppendChar(Char);
	}

	Result.Add(Value);
	return Result;
}

