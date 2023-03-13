// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPickup.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ShooterUtils.h"

bool AAmmoPickup::GivePickupTo(APawn* Pawn)
{
	const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(Pawn);
	if(!HealthComponent || HealthComponent->IsDeath()) return false;

	const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(Pawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
