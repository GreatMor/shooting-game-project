// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UShooterRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UShooterRespawnComponent();

	void Respawn(int32 RespawnTime);
	int32 GetRespawnCountdown() const { return RespawnCountdown; };
	bool IsRespawnInProgress()const ;

private:

	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountdown = 0;

	void RespawnTimerUpdate(); 
};
