// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UNREALPRACTICE_API DialogueFileReader
{
public:
	DialogueFileReader();
	~DialogueFileReader();

	FString LoadDialogueFromFile(const FString& FilePath);
};
