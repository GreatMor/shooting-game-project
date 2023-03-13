// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPickup.h"
#include "ShooterUtils.h"
#include "Components/HealthComponent.h"

bool AHealthPickup::GivePickupTo(APawn* Pawn)
{
	const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(Pawn);
	if (!HealthComponent || HealthComponent->IsDeath()) return false;

	return HealthComponent->TryToAddHealth(AmmountHealth);
}
