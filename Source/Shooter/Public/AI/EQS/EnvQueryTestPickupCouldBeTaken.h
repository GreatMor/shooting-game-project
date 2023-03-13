// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTestPickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UEnvQueryTestPickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEnvQueryTestPickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);

protected: 
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
