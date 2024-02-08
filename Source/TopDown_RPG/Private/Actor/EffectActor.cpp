// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BaseAttributeSet.h"

// Sets default values
AEffectActor::AEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);

	/** TODO: Change this to apply a GameplayEffect. For now, using const_cast as a hack! */
	if (ASCInterface)
	{
		const UBaseAttributeSet* AttributeSet = Cast<UBaseAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBaseAttributeSet::StaticClass()));
		
		UBaseAttributeSet* MutableAttributeSet = const_cast<UBaseAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

