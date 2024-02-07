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
	PlayerCharacterState = GetPlayerState<APlayerCharacterState>();
	if (PlayerCharacterState)
	{
		PlayerCharacterState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerCharacterState, this);
		AbilitySystemComponent = PlayerCharacterState->GetAbilitySystemComponent();
		AttributeSet = PlayerCharacterState->GetAttributeSet();
	}
}

/** Init Ability Actor Info for the server */
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Possessed By Called")));

	PlayerController = Cast<APlayerController>(NewController);

	if (PlayerController)
	{
		InitAbilityActorInfo();
	}
}

/** Init Ability Actor Info for the client */
void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("OnRep_PlayerState Called")));

	InitAbilityActorInfo();
}
