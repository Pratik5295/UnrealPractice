// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FDialogueNode.h"
#include "DialogueFileReader.h"
#include <Components/TextRenderComponent.h>
#include "Components/BoxComponent.h"
#include "DialogueTrigger.generated.h"



class ADialogue;

UCLASS()
class UNREALPRACTICE_API ADialogueTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueTrigger();

private:

	bool canStartConvo = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category = "Dialogue")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	FString DialogueFilePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueNode> DialogueMessages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	ADialogue* activeDialogue;

	//UI elements
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dialogue")
	UTextRenderComponent* InteractionUI;
	

	// Overlap functions
	UFUNCTION(BlueprintCallable)
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ReadDialogueFile();

	DialogueFileReader* FileReader;

	void UpdateConvoStat(bool _ready)
	{
		canStartConvo = _ready;

		if (InteractionUI)
		{
			InteractionUI->SetVisibility(_ready);
		}
	}

};
