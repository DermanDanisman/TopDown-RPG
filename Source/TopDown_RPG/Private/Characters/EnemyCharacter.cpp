// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "TopDown_RPG/TopDown_RPG.h"
/** Ability System */
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	/** This is in case for we need to change CursorTrace from ForObjects to ForChannels */
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	/** How gameplay effects will be replicated to clients */
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/** Setting Init Ability Actor Info for AI-Controlled Character */
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

/** Enables a custom depth pass for the enemy's mesh and weapon, 
setting a stencil value that can be referenced in materials or post-process effects to apply a highlighting effect */
void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	// TODO: Remove Later!
	FString ActorName;
	GetName(ActorName);
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("EnemyCharacter %s: HighlightActor Called"), *ActorName));
}

/** Disables the custom depth rendering for the enemy's mesh and weapon, effectively removing the highlight effect. */
void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);

	// TODO: Remove Later!
	FString ActorName;
	GetName(ActorName);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("EnemyCharacter %s: UnHighlightActor Called"), *ActorName));
}

