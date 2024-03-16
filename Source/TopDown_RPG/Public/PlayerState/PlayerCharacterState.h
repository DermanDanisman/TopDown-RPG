// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
/* Interfaces */
#include "AbilitySystemInterface.h"
#include "PlayerCharacterState.generated.h"

/** Forward Declaring Classes */
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API APlayerCharacterState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	APlayerCharacterState();

public:

	/******************
	* Getter Functions
	*/

	// IAbilitySystemInterface - Returns the ability system component to use for this actor.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

protected:

	/*****************
	* Ability System
	*/

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;
};
