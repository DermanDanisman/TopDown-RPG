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

	void InitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

public:

	/** Pointer to Wiget that will be shown as HUD
	HUD is a good class to create both the OverlayWidget and the WidgetController itself. */
	UPROPERTY(VisibleAnywhere, Category = "References")
	TObjectPtr<UBaseUserWidget> OverlayWidget;

private:

	/** HUD is a good class to create both the OverlayWidget and the WidgetController itself. */
	UPROPERTY(VisibleAnywhere, Category = "References")
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;


private:

	/*****************
	* Class References
	*/

	UPROPERTY(EditAnywhere, Category = "TSubclassOf")
	TSubclassOf<UBaseUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere, Category = "TSubclassOf")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
