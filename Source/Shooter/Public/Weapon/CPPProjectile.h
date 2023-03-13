// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UShooterFXSystemComponent;
class UNiagaraSystem;

UCLASS() 
class SHOOTER_API ACPPProjectile : public AActor
{
    GENERATED_BODY()

public:

    ACPPProjectile();
    void SetShotDirection(const FVector &Direction) { ShotDirection = Direction; };

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 200.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.f;

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    UShooterFXSystemComponent* FXComponent;

protected:

    virtual void BeginPlay() override;
 
private:
    FVector ShotDirection;
    
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                       UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
    
    AController* GetController() const;

};

