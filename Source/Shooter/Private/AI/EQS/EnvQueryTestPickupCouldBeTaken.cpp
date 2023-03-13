// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTestPickupCouldBeTaken.h"
#include "Pickups/BasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTestPickupCouldBeTaken::UEnvQueryTestPickupCouldBeTaken(const FObjectInitializer& ObjectInitializer) 
			: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTestPickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	bool WantsBeTackable = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{		
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());	
		const auto PickupActor = Cast<ABasePickup>(ItemActor);

		if(!PickupActor) continue;

		const auto CouldBeTaken = PickupActor->CouldBeTaken();	
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTackable);				
	}
}
