// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "GameplayEffectTypes.h"

/** This setup allows for a robust system where gameplay systems (like health and mana changes) can communicate changes directly to the UI in a decoupled manner,
enabling real-time updates and reducing the need for polling or tightly coupling UI code to gameplay logic.
It's a common pattern in games using the Gameplay Ability System to manage player abilities, stats, and effects. */

/** This function grabs the current values of attributes from the BaseAttributeSet and broadcasts them using the previously defined multicast delegates.
This is typically called when the widget is first displayed to ensure the UI shows the current state of the character's attributes. */
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(BaseAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(BaseAttributeSet->GetMaxMana());
}

/** Sets up bindings between the attribute change events in the ability system component and the controller's methods. 
When an attribute changes, the appropriate method in the widget controller is called, which in turn broadcasts the change to any listeners. */
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);

	/** We want to be able to respond to when those attributes change and the ability system component has a function for it called GetGameplayAttributeValueChangeDelegate.
	Since GetGameplayAttributeValueChangeDelegate is not a DYNAMIC_MULTICAST_DELEGATE we cannot use AddDynamic, instead we need to use AddUObject. */

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

/** These methods (HealthChanged, MaxHealthChanged, ManaChanged, MaxManaChanged) are callbacks invoked when their respective attributes change.
They broadcast the new attribute values using the delegates. */
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& AttributeData) const
{
	OnHealthChanged.Broadcast(AttributeData.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& AttributeData) const
{
	OnMaxHealthChanged.Broadcast(AttributeData.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& AttributeData) const
{
	OnManaChanged.Broadcast(AttributeData.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& AttributeData) const
{
	OnMaxManaChanged.Broadcast(AttributeData.NewValue);
}
