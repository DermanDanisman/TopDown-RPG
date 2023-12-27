// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{

}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHighlighted)
		DrawDebugSphere(GetWorld(), GetActorLocation(), 50.f, 12.f, FColor::Red, false);
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::HighlightActor()
{
	bHighlighted = true;
	FString Name = GetName();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Name: %s"), *Name));
}

void AEnemyCharacter::UnHighlightActor()
{
	bHighlighted = false;
}

