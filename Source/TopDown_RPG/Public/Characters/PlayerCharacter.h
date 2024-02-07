// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/** Forward Declaring Classes */
class APlayerController;
class APlayerCharacterState;

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

public:

	/**
	* 
	*/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:

	/*************
	* References
	*/
	UPROPERTY(VisibleAnywhere, Category = "References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(VisibleAnywhere, Category = "References")
	TObjectPtr<APlayerCharacterState> PlayerCharacterState;

private:

	/***************
	* Ability System
	*/
	void InitAbilityActorInfo();
};
