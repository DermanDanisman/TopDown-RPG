// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/* Forward Declaring Classes */
class ACharacter;
class UInputMappingContext;
class UInputAction;
class IHighlightInterface;
/* Forward Declaring Structs */
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:

	APlayerCharacterController();
	virtual void PlayerTick(float DeltaTime);

protected:

	virtual void BeginPlay();
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:

	/********************
	* Essential Settings
	*/

	UFUNCTION()
	void SetCursorSettings();

	/**************
	* Cursor Trace
	*/

	void CursorTrace();
	IHighlightInterface* LastActor;
	IHighlightInterface* ThisActor;
	UPROPERTY(EditAnywhere, Category = "Cursor Trace")
	TArray<TEnumAsByte<EObjectTypeQuery>> CursorTraceObjectType;

private:

	/************
	* References
	*/

	UPROPERTY(VisibleAnywhere, Category = "References")
	TObjectPtr<ACharacter> ControlledCharacter = nullptr;

	/*******
	* Input
	*/

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
};
