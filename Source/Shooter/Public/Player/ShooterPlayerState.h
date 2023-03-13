// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	int32 GetTeamID() const { return TeamID; };
	void SetTeamID(int32 ID) {TeamID = ID;};

	FLinearColor GetTeamColor() const { return TeamColor; };
	void SetTeamColor(FLinearColor Color) { TeamColor = Color; };

	void AddKill() { ++KillsNum; };
	int32 GetKillsNum() const {return KillsNum; };

	void AddDeath() { ++DeathNum; }; 
	int32 GetDeathNum() { return DeathNum; };

	void LogInfo();

private:
	int32 TeamID;
	FLinearColor TeamColor;	
	int32 KillsNum = 0; 
	int32 DeathNum = 0;
};
