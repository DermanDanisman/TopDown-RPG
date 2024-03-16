// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UObject> WidgetController;

protected:

	/** Whenever we set the WidgetController for a given widget, we'll also call this function WidgetControllerSet().
	And as soon as that happens, anything we want in the blueprint that we would like to do in response to the WidgetControllerSet(), we'll do that in the blueprint.
	So that means we should associate setting the WidgetController with calling WidgetControllerSet().
	These should be tied closely together. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Widget Controller")
	void WidgetControllerSet();
};
