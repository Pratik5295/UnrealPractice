// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDialogueOption.generated.h"

USTRUCT(BlueprintType)
struct UNREALPRACTICE_API FDialogueOption
{
	GENERATED_BODY()
public:
	FDialogueOption();
	~FDialogueOption();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	int32 NextInteger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString OptionMessage;


};
