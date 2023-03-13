// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIBaseController.h"
#include "AI/AICharacter.h"
#include "AIController.h"
#include "Components/ShooterAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ShooterRespawnComponent.h"

AAIBaseController::AAIBaseController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UShooterAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("RespawnComponent");

	bWantsPlayerState = 1;
}

void AAIBaseController::OnPossess(APawn* IsPawn)
{
	Super::OnPossess(IsPawn);
	const auto AICharacter = Cast<AAICharacter>(IsPawn);

	if(AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}

void AAIBaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	if(!AimActor) return;
	//UE_LOG(LogTemp, Warning, TEXT("focus %s "),*AimActor->GetName())
	SetFocus(AimActor);
}

AActor* AAIBaseController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
