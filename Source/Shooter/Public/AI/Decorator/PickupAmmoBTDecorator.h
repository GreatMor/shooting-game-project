// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PickupAmmoBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UPickupAmmoBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPickupAmmoBTDecorator();

protected: 

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<ABaseGun> WeaponTaype;
};
