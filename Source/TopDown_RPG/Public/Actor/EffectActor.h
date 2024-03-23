// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

/** Forward Declaring Classes */
class USphereComponent;
class UGameplayEffect;

UCLASS()
class TOPDOWN_RPG_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;


};
