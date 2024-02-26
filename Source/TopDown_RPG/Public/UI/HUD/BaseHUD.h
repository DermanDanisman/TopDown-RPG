// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/** Forward Declaring Classes */
class UBaseUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;

/** Forward Declaring Structs */
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API ABaseHUD : public AHUD
{
	GENERATED_BODY()


public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

public:

	/** Pointer to Wiget that will be shown as HUD */
	UPROPERTY()
	TObjectPtr<UBaseUserWidget> OverlayWidget;

private:

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;


private:


	/** */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseUserWidget> OverlayWidgetClass;

	/** */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
