// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
/* Interfaces */
#include "AbilitySystemInterface.h"
/* Ability System */
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AEffectActor::AEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

/** This function applies a gameplay effect to a target actor. */
void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	/** Attempts to retrieve the UAbilitySystemComponent associated with the target actor. This component is essential for using the Gameplay Ability System. */
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	/** Checks if the target actor has an AbilitySystemComponent. If not, it exits the method since applying a gameplay effect is not possible. */
	if (TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	/** Creates a new effect context handle. This handle is used to provide additional context about the effect, such as who initiated it. */
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	/** Adds the AEffectActor instance as the source object to the effect context. This means that AEffectActor is considered the origin of the effect being applied. */
	EffectContextHandle.AddSourceObject(this);
	/** Creates a gameplay effect specification from the given effect class. The effect's level is set to 1.0f temporarily, and the previously created effect context is used. */
	FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	/** Applies the gameplay effect to the target actor itself, based on the specifications defined in EffectSpecHandle. */
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


