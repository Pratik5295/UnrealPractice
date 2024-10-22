// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealPracticeGameMode.h"
#include "UnrealPracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"


AUnrealPracticeGameMode::AUnrealPracticeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

