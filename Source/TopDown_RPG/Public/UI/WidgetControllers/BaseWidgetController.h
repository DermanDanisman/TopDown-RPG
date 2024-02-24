// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWidgetController.generated.h"

/** Forward Declaring Classes */
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
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
