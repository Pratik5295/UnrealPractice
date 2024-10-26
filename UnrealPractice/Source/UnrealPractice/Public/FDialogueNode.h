// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueNode.generated.h"


USTRUCT(BlueprintType)
struct UNREALPRACTICE_API FDialogueNode
{
	GENERATED_BODY()	

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	FString SpeakerName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	FString Message;

	FDialogueNode();
	~FDialogueNode();

	//A helper const function to check  if the struct has meaningful values
	bool IsEmpty() const
	{
		return SpeakerName.IsEmpty() && Message.IsEmpty();
	}
};
