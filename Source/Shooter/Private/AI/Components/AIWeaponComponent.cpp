// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/AIWeaponComponent.h"
#include "BaseGun.h"

void UAIWeaponComponent::StartFire()
{
	if(!CanFire()) return;
	if (CurrentWeapon->IsAmmoEmpty())
	{
		 NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UAIWeaponComponent::NextWeapon()
{
	if (!CanFire()) return;
	int32 NextIndex = ((CurrentWeaponIndex + 1) % Weapons.Num());

	while (NextIndex != CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex+1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
