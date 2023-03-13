// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CPPProjectile.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "FXComponents/ShooterFXSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACPPProjectile::ACPPProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000;
    MovementComponent->ProjectileGravityScale = 0;

    FXComponent = CreateDefaultSubobject<UShooterFXSystemComponent>("FXSystemComponent");
}
void ACPPProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(MovementComponent->InitialSpeed != 0);
    check(MovementComponent->ProjectileGravityScale == 0);
    check(FXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->OnComponentHit.AddDynamic(this, &ACPPProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ACPPProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(!GetWorld()) return;

    MovementComponent->StopMovementImmediately();
    Destroy();

     UGameplayStatics::ApplyRadialDamage(GetWorld(), // 
                                       DamageAmount, //
                                       GetActorLocation(), //
                                       DamageRadius, //
                                       UDamageType::StaticClass(),//
                                       {GetOwner()},               //
                                       this,//
                                       GetController(),             //
                                       DoFullDamage);
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.f);
    FXComponent->PlayImpactFX(Hit);
}

AController *ACPPProjectile::GetController() const 
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
