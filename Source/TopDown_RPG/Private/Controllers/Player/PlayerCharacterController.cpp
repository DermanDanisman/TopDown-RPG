// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Player/PlayerCharacterController.h"
/* Game Framework */
#include "GameFramework/Character.h"
/* Enhanced Input */
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
/* Interfaces */
#include "Interfaces/HighlightInterface.h"

APlayerCharacterController::APlayerCharacterController()
{
	/* Player Controller is designated to be a replicated entity */
	bReplicates = true;
}

void APlayerCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void APlayerCharacterController::CursorTrace()
{
	FHitResult CursorHit;
	//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	GetHitResultUnderCursorForObjects(CursorTraceObjectType, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	/* LastActor will store what ThisActor was before we updated it. 
	In other words, what it was last frame so we can check the values of these. */
	LastActor = ThisActor;
	ThisActor = Cast<IHighlightInterface>(CursorHit.GetActor());

	/**
	* Line trace from cursor. There are several scenerios:
	* A. LastActor is null and ThisActor is null
	*	- Do nothing
	* B. LastActor is null and ThisActor is valid
	*	- Highlight ThisActor
	* C. LastActor is Valid and ThisActor is null
	*	- UnHighlight LastActor
	* D. Both Actors are valid, but LastActor != ThisActor
	*	- UnHighlight LastActor, and Highlight ThisActor
	* E. Both Actors are valid, and LastActor == ThisActor
	*	- Do nothing
	*/

	if (ThisActor != LastActor)
	{
		if (LastActor != nullptr)
		{
			LastActor->UnHighlightActor();
		}

		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = CastChecked<ACharacter>(GetPawn());

	/* The check() macro in Unreal Engine is indeed a form of assert.
	It's used to verify that a certain condition is true during runtime in development builds (like Debug and Development builds).
	If the condition inside check() evaluates to false, the program will halt, and Unreal Engine will provide diagnostic information, such as the file and line number where the failure occurred.
	The primary purpose of check() is to catch programming errors and incorrect assumptions during development, rather than being used as a control flow mechanism in the final product. */
	/* Using an assert. "check" here and we'll check the DefaultContext pointer.
	So check is going to halt execution if this condition fails and DefaultContext being a pointer will be evaluated as false if it hasn't been set yet. */
	check(DefaultContext);

	/* Adding Mapping Context */
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(InputLocalPlayerSubsystem)
	InputLocalPlayerSubsystem->AddMappingContext(DefaultContext, 0);

	SetCursorSettings();
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/* Binding Input Actions to their respective functions */
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// Moving
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
}

void APlayerCharacterController::SetCursorSettings()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

// Input Function responsible for character movement
void APlayerCharacterController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//FRotator ForwardMakeRot = UKismetMathLibrary::MakeRotator(0.f, 0.f, Rotation.Yaw);
	//FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(ForwardMakeRot);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	ControlledCharacter->AddMovementInput(ForwardDirection, InputAxisVector.Y);

	//FRotator RightMakeRot = UKismetMathLibrary::MakeRotator(0.f, 0.f, Rotation.Yaw);
	//FVector RightDirection = UKismetMathLibrary::GetRightVector(RightMakeRot);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	ControlledCharacter->AddMovementInput(RightDirection, InputAxisVector.X);
}
