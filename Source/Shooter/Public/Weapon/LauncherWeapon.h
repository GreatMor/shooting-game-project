// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseGun.h"
#include "LauncherWeapon.generated.h"

class ACPPProjectile;

UCLASS()
class SHOOTER_API ALauncherWeapon : public ABaseGun
{
	GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, Category = "baseline")
    TSubclassOf<ACPPProjectile> ProjectileClass;
	
protected:

	virtual void StartFire() override;
	virtual void MakeShot() override;
};
