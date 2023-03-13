// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseGun.h"
#include "RifleWeapon.generated.h"

class UShooterFXSystemComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTER_API ARifleWeapon : public ABaseGun
{
	GENERATED_BODY()

    ARifleWeapon();

 protected:

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    float TimeBetweenShort = 0.1f;

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    float BulletSpret = 1.5;

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    float DamagAmmo = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString  TraceTargetName = "TraceTarget";

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    UShooterFXSystemComponent* FXComponent;

 protected:

    virtual void BeginPlay() override;
    virtual void StartFire() override;
	virtual void StopFire() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &Start, FVector &End) const override;
    void MakeDamage(const FHitResult &HitResult);

  private:

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    FTimerHandle ShotTimerHandle;

    void InitMuzzleFX();
    void SetMuzleFXVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    AController* GetController() const;
};
