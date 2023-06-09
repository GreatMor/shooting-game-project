// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Components/WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;	
};
