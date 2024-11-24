// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueFileReader.h"

DialogueFileReader::DialogueFileReader()
{
}

DialogueFileReader::~DialogueFileReader()
{
}

TArray<FString> DialogueFileReader::LoadDialogueFromFile(const FString& FilePath)
{
	TArray<FString> CsvLines;

	FString FullFilePath = FPaths::ProjectContentDir() / FilePath + TEXT(".csv");

	FFileHelper::LoadFileToStringArray(CsvLines, *FullFilePath);

	return CsvLines;
}
