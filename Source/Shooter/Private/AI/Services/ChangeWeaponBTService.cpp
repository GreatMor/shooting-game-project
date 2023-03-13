// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ChangeWeaponBTService.h"
#include "Components/WeaponComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"

UChangeWeaponBTService::UChangeWeaponBTService()
{
	NodeName = "Change Weapon";
}
void UChangeWeaponBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);	
}

