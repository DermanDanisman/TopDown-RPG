// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

/** Forward Declaring Structs */
struct FOnAttributeChangeData;

/** Make dynamic multicast delegates to assign events to them in Blueprint and our widget blueprint specifically. 
That's why I want them to be dynamic and multicast because multiple blueprints, multiple widget blueprints may want to bind to these delegates so that they can update.
These are defined to notify other parts of the game (such as UI widgets) about changes to certain attributes.
These delegates allow for a flexible event system where multiple subscribers can listen for and react to attribute changes.*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOPDOWN_RPG_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()
	
public:

	/** A function meant to be overridden to broadcast the initial values of attributes when the widget controller is first initialized. */
	virtual void BroadcastInitialValues() override;

	/** A function intended to be overridden to set up callbacks that respond to changes in the character's attributes. */
	virtual void BindCallbacksToDependencies() override;


	/** Properties are exposed to Blueprints (BlueprintAssignable) to allow binding in the Unreal Engine's Blueprint editor.
	These properties represent the dynamic multicast delegates declared earlier. */

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:

	/********************
	* Callback Functions
	*/

	/** These methods (HealthChanged, MaxHealthChanged, ManaChanged, MaxManaChanged) are callbacks invoked when their respective attributes change.
	They broadcast the new attribute values using the delegates. */

	void HealthChanged(const FOnAttributeChangeData& AttributeData) const;
	void MaxHealthChanged(const FOnAttributeChangeData& AttributeData) const;
	void ManaChanged(const FOnAttributeChangeData& AttributeData) const ;
	void MaxManaChanged(const FOnAttributeChangeData& AttributeData) const;
};
