// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (MinClamp = 1, MaxClamp = 100))
	float AmmountHealth = 100;
private:
	virtual bool GivePickupTo(APawn* Pawn) override;
};
