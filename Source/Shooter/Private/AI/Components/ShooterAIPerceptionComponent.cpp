// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/ShooterAIPerceptionComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"


AActor* UShooterAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;
	
	const auto Controller =  Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BastDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(PercieveActor);
		const auto PercievePawn = Cast<APawn>(PercieveActor);
		bool AreEnemies = PercievePawn && ShooterUtils::AreEnemies(Controller, PercievePawn->Controller);
		
		if (HealthComponent && !HealthComponent->IsDeath() && AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BastDistance)
			{
				BastDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
