// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"
#include "UI/Widgets/BaseUserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

/** This function is responsible for retrieving an UOverlayWidgetController instance. 
The UOverlayWidgetController is a custom class that manages interactions and 
data flow between the game and a specific UMG widget (an overlay in this case). */
UOverlayWidgetController* ABaseHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		/** So NewObject is how we can create a new object. */
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

/** Initializing OverlayWidget and its Widget Controller and assign it to the widget. */
void ABaseHUD::InitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized!"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized!"));

	/** Creating Widget using TSubclassOf<OverlayWidgetClass> */
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	/** Casting Widget to UBaseUserWidget and initialize it to OverlayWidget */
	OverlayWidget = Cast<UBaseUserWidget>(Widget);


	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* OverlayWC = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayWC);

	Widget->AddToViewport();
}

