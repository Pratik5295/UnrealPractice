// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealPracticeCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DialogueManager.h"
#include "UnrealPracticeProjectile.h"
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AUnrealPracticeCharacter

AUnrealPracticeCharacter::AUnrealPracticeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AUnrealPracticeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Find the dialogue manager

	DialogueManager = Cast<ADialogueManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass()));

	if (DialogueManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dialogue Manager exists through code!!"));

		DialogueManager->OnConvoUpdateEvent.AddUObject(this, &AUnrealPracticeCharacter::OnDialogueToggled);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AUnrealPracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		/*EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);*/

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUnrealPracticeCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUnrealPracticeCharacter::Look);

		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AUnrealPracticeCharacter::Interaction);
	
		//Dialogue Move Handling
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AUnrealPracticeCharacter::HandleMove);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUnrealPracticeCharacter::OnDialogueToggled(bool isActive)
{
	if (isActive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Dialogue Widget is now open"));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dialogue Widget now closed"));
	}

	//Sets the dialogue open value
	isDialogueActive = isActive;
}


void AUnrealPracticeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (!isDialogueActive)
		{
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void AUnrealPracticeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		if (!isDialogueActive) 
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void AUnrealPracticeCharacter::Interaction(const FInputActionValue& Value)
{
	if (DialogueManager)
	{
		DialogueManager->ShowNextMessage();
	}
}

void AUnrealPracticeCharacter::HandleMove(const FInputActionValue& Value)
{
	if (!DialogueManager) return;

	if (!isDialogueActive) return;

	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		DialogueManager->HandlePlayerInput(MoveVector.Y);
	}
}