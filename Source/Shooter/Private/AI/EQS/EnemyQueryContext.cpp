// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnemyQueryContext.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryActor = Cast<AActor>(QueryInstance.Owner.Get());

	const auto Blackbord = UAIBlueprintHelperLibrary::GetBlackboard(QueryActor);
	if(!Blackbord) return;

	const auto ContextActor = Blackbord->GetValueAsObject(EnamyActorKayName);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
