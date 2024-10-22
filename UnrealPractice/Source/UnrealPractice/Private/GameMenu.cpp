// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//Bind buttons
	if (UButton* StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton"))))
	{
		StartButton->OnClicked.AddDynamic(this, &UGameMenu::OnStartClicked);
	}

	if (UButton* QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton"))))
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameMenu::OnQuitClicked);
	}
}

void UGameMenu::OnStartClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Start clicked"));
	UE_LOG(LogTemp, Log, TEXT("Button clicked"));
	UGameplayStatics::OpenLevel(this, FName("NextLevel"));
}

void UGameMenu::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, 
		EQuitPreference::Quit, true);
}

