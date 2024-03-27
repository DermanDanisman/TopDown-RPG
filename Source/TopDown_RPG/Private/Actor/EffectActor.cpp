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

/**************************************************************************** Note to Self : ****************************************************************************************/
/** So once we've applied a gameplay effect, that gameplay effect becomes active and apply functions like ApplyGameplayEffectSpecToSelf() return a handle to that effect.
So we can always use that handle for something later, such as removing it if it's an InfiniteGameplayEffect. So we need to store this handle.
We need to be careful about the way we do this. If we're just thinking about one player character in the world running around picking up these effect actors,
then we could store the active gameplay effect that we've applied and then OnEndOverlap just take that OtherActor and remove that active effect.
But realistically, games are not that simple. We might have multiple actors overlapping. Some of them may have ability system components, some may not.
And we can't just assume that TargetActor on EndOverlap is the correct actor for any given effect handle.
And if multiple actors are overlapping and we're setting a single effect handle variable, then we're overwriting it and losing the effect handle that that variable stored before.
In other words, this requires a bit more care. */
/**************************************************************************** Note to Self : ****************************************************************************************/

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
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	/** Data is a shared pointer. To get that raw pointer we can call Data.Get() on that and that returns us a pointer to gameplay effect spec. 
	What we want from the EffectSpec is the GameplayEffect itself. This pointer can be dereferenced and the GameplayEffect itself is called Def.
	So inside the SpecHandle we have data that's the GameplayEffectSpec. Inside the Spec we have Def, which is the GameplayEffect.
	Now this being a TObject pointer means we have to call Get() yet again and that gives us the raw pointer which we can access to get all of these things on the gameplay effect itself. */
	const bool bIsInfiniteEffect = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfiniteEffect && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap && ActiveEffectHandle.WasSuccessfullyApplied())
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	}


	/** DEBUG!
	for (FActiveGameplayEffectsContainer::ConstIterator ActiveEffectItr = 
		TargetAbilitySystemComponent->GetActiveGameplayEffects().CreateConstIterator(); ActiveEffectItr; ++ActiveEffectItr)
	{
		const AActor* Causer = ActiveEffectItr->Spec.GetEffectContext().GetEffectCauser();
		const UObject* SourceObject = ActiveEffectItr->Spec.GetEffectContext().GetSourceObject();
		const TObjectPtr<const UGameplayEffect> Effect = ActiveEffectItr->Spec.Def;

		UE_LOG(LogTemp, Log, TEXT("Effect is: %s / Source Object is %s / Causer is %s "),
			*Effect->GetName(),
			*SourceObject->GetName(),
			*Causer->GetName());
	}

	TargetAbilitySystemComponent->PrintDebug();
	 DEBUG! */
}

void AEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
}

void AEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetAbilitySystemComponent)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto HandlePair : ActiveEffectHandles)
		{
			if (TargetAbilitySystemComponent == HandlePair.Value)
			{
				TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}



