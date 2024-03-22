// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/BaseWidgetController.h"

/** 
* This is the base WidgetController, all the WidgetControllers will derive from this class.
*/

/** Setting Widget Controller Parameters using struct and initializing the pointers. */
void UBaseWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

/** A virtual function meant to be overridden to broadcast the initial values of attributes when the widget controller is first initialized. */
void UBaseWidgetController::BroadcastInitialValues()
{

}

/** Another virtual function intended to be overridden to set up callbacks that respond to changes in the character's attributes. */
void UBaseWidgetController::BindCallbacksToDependencies()
{

}
