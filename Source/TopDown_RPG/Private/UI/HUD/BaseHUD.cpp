// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"
/** Widgets */
#include "UI/Widgets/BaseUserWidget.h"
/** Widget Controllers */
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
		/** Initializing the newly created OverlayWidgetController with parameters (WCParams) relevant for controlling the widget. */
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		/** Binding Overlay Widget Controller callbacks to the dependencies. When the related attributes change, we'll get the change broadcast. */
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

/** Initializes the OverlayWidget by creating it, setting up its controller, and adding it to the game's viewport. */
void ABaseHUD::InitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized!"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized!"));

	/** Creates an instance of UUserWidget using CreateWidget<UUserWidget>(), indicating the class to instantiate (OverlayWidgetClass). */
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	/** Casting Widget to UBaseUserWidget and initialize it to OverlayWidget */
	OverlayWidget = Cast<UBaseUserWidget>(Widget);

	/** Constructs a FWidgetControllerParams structure, packaging relevant data (PC, PS, ASC, AS) to be used by the widget controller. */
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	/** Calls GetOverlayWidgetController() with the constructed parameters to retrieve (or create) the widget controller. */
	UOverlayWidgetController* OverlayWC = GetOverlayWidgetController(WidgetControllerParams);

	/** Associates the retrieved OverlayWC (Overlay Widget Controller) with the overlay widget,
	allowing the controller to manage the widget based on game data and player interactions. */
	OverlayWidget->SetWidgetController(OverlayWC);
	/** Calls OverlayWidgetController->BroadcastInitialValues() to initialize or update the widget's display based on current game state or data. */
	OverlayWidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

