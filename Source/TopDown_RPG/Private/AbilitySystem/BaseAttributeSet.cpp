// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	/** Get##PropertyName##Attribute(), Get##PropertyName(), Set##PropertyName, Init##PropertyName all comes from AttributeSet.h. 
	Example:
	GetHealthAttribute() -> Gets the actual attribute which is the type of FGameplayAttribute 
	GetHealth() -> Gets Numerical Value of an Attribute
	SetHealth() -> Sets Numeric Attribute Base
	InitHealth() -> Sets BaseValue and CurrentValue of an Attribute */

	InitHealth(25.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(100.f);
}

/** Marks variables as replicated */
void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/** REPNOTIFY_Always means that if the value is set on the server, replicate it and on the client, that value will be updated and set.
	Now compare that to on changed, which is the default option. With on changed if you set the value of health on the server and that value hasn't changed, 
	then there will be no replication. This is a sort of optimization if you're setting it to the same value that it already has, 
	there's no need to replicate it in most cases. But for GAS we want to replicate it anyway because if we're setting it, we may want to respond to the act of setting it. 
	Whether we've set it to a new value or its own same value, you may want to respond anyway, even if its numerical value hasn't changed.*/

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Health, OldHealth);
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Mana, OldMana);
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxMana, OldMaxMana);
}
