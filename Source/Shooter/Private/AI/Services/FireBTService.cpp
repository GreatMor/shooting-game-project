// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FireBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponComponent.h"
#include "AI/Components/ShooterAIPerceptionComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"

UFireBTService::UFireBTService()
{
	NodeName = "Fire";
}

void UFireBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlcakBord = OwnerComp.GetBlackboardComponent();
	
	const auto HasAim = BlcakBord && BlcakBord->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{		
		const auto Pawn = Controller->GetPawn();
		if (Pawn)
		{
			const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(Pawn);
			if (WeaponComponent)
			{
				HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
			}
		}	
	}
	Super::TickNode( OwnerComp,NodeMemory,DeltaSeconds);
}
