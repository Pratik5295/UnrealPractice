// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueFileReader.h"

DialogueFileReader::DialogueFileReader()
{
}

DialogueFileReader::~DialogueFileReader()
{
}

FString DialogueFileReader::LoadDialogueFromFile(const FString& FilePath)
{
	FString FileContent; 

	FString FullFilePath = FPaths::ProjectContentDir() / FilePath + TEXT(".txt");

	FFileHelper::LoadFileToString(FileContent, *FullFilePath);

	return FileContent;
}
