// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWidgetController.generated.h"

/**
 * This is the base WidgetController, all the WidgetControllers will derive from this class.
 */

/** Forward Declaring Classes */
class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType) 
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}

	/** Define the constructor right here. Colon means use an initializer list. Between the colon and the curly brackets, we initialize the variables */
	/** This will be a comma separated list. This is known as the member initializer list. */
	/** We have a struct that can receive these four key variables when we create one, and that's going to make it easy to initialize a widget controller. */
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};

UCLASS()
class TOPDOWN_RPG_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams WCParams);

	/** Any WidgetController that inherits this function should be able to broadcast its own unique initial values. */
	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<UAttributeSet> AttributeSet;
};
