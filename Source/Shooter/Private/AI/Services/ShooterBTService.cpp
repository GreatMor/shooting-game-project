// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ShooterBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Components/ShooterAIPerceptionComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"

UShooterBTService::UShooterBTService()
{
	NodeName = "Find Enemy";
}

void UShooterBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (BlackBoard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = ShooterUtils::GetShooterPLayerComponent<UShooterAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp,NodeMemory, DeltaSeconds);
}
