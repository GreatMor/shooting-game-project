// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/PickupAmmoBTDecorator.h"
#include "ShooterUtils.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"

UPickupAmmoBTDecorator::UPickupAmmoBTDecorator()
{
	NodeName = "Find Ammo";
}

bool UPickupAmmoBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponTaype);
}