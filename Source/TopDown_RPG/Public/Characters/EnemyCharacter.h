// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
/* Interfaces */
#include "Interfaces/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API AEnemyCharacter : public ACharacterBase, public IHighlightInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	virtual void Tick(float DeltaTime);

public:

	/* EnemyCharacter cannot instantiate abstract class. 
	Because, as soon as we added a pure virtual function to HighlightInterface, 
	it became an abstract class and you cannot instantiate an abstract class without overriding its pure virtual functions. 
	So we have to override both of these. */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
