// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

/** Forward Declaring Structs */
struct FOnAttributeChangeData;

/** Make dynamic multicast delegates to assign events to them in Blueprint and our widget blueprint specifically. 
That's why I want them to be dynamic and multicast because multiple blueprints, multiple widget blueprints may want to bind to these delegates so that they can update. */

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

	/** Broadcasting initial values in this WidgetController */
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;


	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:

	void HealthChanged(const FOnAttributeChangeData& AttributeData) const;
	void MaxHealthChanged(const FOnAttributeChangeData& AttributeData) const;
	void ManaChanged(const FOnAttributeChangeData& AttributeData) const ;
	void MaxManaChanged(const FOnAttributeChangeData& AttributeData) const;
};
