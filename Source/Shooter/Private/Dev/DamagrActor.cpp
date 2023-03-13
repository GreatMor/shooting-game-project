// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/DamagrActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "IceDamageType.h"
#include "FireDamageType.h"
//#include <destructible/ModuleDestructible.h>
// Sets default values
ADamagrActor::ADamagrActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SceneComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADamagrActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamagrActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {},
                                    this,nullptr,DoFullDamage );
}

