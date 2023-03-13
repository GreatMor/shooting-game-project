// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PercentHealthTDecorator.generated.h"

UCLASS()
class SHOOTER_API UPercentHealthTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPercentHealthTDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "AI")
	float HealthPercent = 0.6f;
};
