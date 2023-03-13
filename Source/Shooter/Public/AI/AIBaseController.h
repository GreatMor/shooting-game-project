// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBaseController.generated.h"

class UShooterAIPerceptionComponent;
class UShooterRespawnComponent;

UCLASS()
class SHOOTER_API AAIBaseController : public AAIController
{
	GENERATED_BODY()
public:
	AAIBaseController();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UShooterAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UShooterRespawnComponent* RespawnComponent;

	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaTime) override;
 
private:
	AActor* GetFocusOnActor() const;
};
