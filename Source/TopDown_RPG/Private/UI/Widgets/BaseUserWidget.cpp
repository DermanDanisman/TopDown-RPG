// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/BaseUserWidget.h"


void UBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (InWidgetController == nullptr)
	{
		// TODO: Remove Later!
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("BaseUserWidget: SetWidgetController: InWidgetController is Invalid!")));
		return;
	}
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
