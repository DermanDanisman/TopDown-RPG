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

void UBaseWidgetController::BroadcastInitialValues()
{

}

/** Binding callbacks to the dependencies of widget controller is something that all widget controllers need to do. 
So we can use this function to bind our callbacks to all those dependencies. */
void UBaseWidgetController::BindCallbacksToDependencies()
{

}
