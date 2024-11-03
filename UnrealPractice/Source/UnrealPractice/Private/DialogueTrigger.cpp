// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTrigger.h"

// Sets default values
ADialogueTrigger::ADialogueTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	activeDialogue = nullptr;

}

// Called when the game starts or when spawned
void ADialogueTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ADialogueTrigger::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)  // Ensure the actor is valid and not self
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s"), *OtherActor->GetName());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Collided with something"));
	}
}

void ADialogueTrigger::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap End with %s"), *OtherActor->GetName());
	}
}

// Called every frame
void ADialogueTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

