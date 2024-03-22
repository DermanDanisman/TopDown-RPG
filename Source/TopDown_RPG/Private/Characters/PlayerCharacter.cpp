// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
/** Controllers */
#include "Controllers/Player/PlayerCharacterController.h"
/** Player State */
#include "PlayerState/PlayerCharacterState.h"
/** Ability System */
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
/** HUD */
#include "UI/HUD/BaseHUD.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	/** The character will only be able to move in the X and Y directions, but not in the Z direction (up or down). 
	GetCharacterMovement()->bConstrainToPlane is used to enable or disable the constraint of a character's movement to a specific plane in Unreal Engine,
	often for specific gameplay mechanics or design choices. */
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

/** Setting Init Ability Actor Info and Initializing AbilitySystemComponent & AttributeSet */
void APlayerCharacter::InitAbilityActorInfo()
{
	// TODO: Remove Later!
	FString ActorName;
	ActorName = GetName();

	PlayerCharacterState = GetPlayerState<APlayerCharacterState>();
	PlayerController = Cast<APlayerCharacterController>(PlayerCharacterState->GetPlayerController());

	checkf(PlayerCharacterState, TEXT("Player Character State Uninitialized!"));
	//checkf(PlayerController, TEXT("Player Controller Uninitialized!"));
	if (PlayerCharacterState && PlayerController)
	{
		PlayerCharacterState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerCharacterState, this);
		AbilitySystemComponent = PlayerCharacterState->GetAbilitySystemComponent();
		AttributeSet = PlayerCharacterState->GetAttributeSet();

		/** Setting OverlayWidgetController variables */
		InitOverlayWidgetInfo();
	}
	else
	{
		// TODO: Remove Later!
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("PlayerCharacter %s: InitAbilityActorInfo: Controller Is Not Valid!"), *ActorName));
	}

	// TODO: Remove Later!
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("PlayerCharacter %s: InitAbilityActorInfo Called"), *ActorName));
}

void APlayerCharacter::InitOverlayWidgetInfo()
{
	ABaseHUD* BaseHUD = Cast<ABaseHUD>(PlayerController->GetHUD());
	if (BaseHUD)
	{
		/** Setting OverlayWidgetController variables */
		BaseHUD->InitOverlayWidget(PlayerController, PlayerCharacterState, AbilitySystemComponent, AttributeSet);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// TODO: Remove Later!
	FString ActorName;
	ActorName = GetName();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("PlayerCharacter %s: Possessed By Called"), *ActorName));

	/** Init Ability Actor Info for the server */
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// TODO: Remove Later!
	FString ActorName;
	ActorName = GetName();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("PlayerCharacter %s: OnRep_PlayerState Called"), *ActorName));

	/** Init Ability Actor Info for the client */
	InitAbilityActorInfo();
}
