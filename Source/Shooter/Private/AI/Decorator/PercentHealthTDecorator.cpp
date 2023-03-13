// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/PercentHealthTDecorator.h"
#include "ShooterUtils.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

UPercentHealthTDecorator::UPercentHealthTDecorator()
{
	NodeName = "Health Percent";
}

bool UPercentHealthTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDeath()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
