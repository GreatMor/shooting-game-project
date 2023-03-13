// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataWidget.generated.h"

class AShooterPlayerState;
class AShooterGameModeBase;

UCLASS()
class SHOOTER_API UGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetCurrentRound() const;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetTotalRound() const;
	
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetRoundSecondsRemaining() const;

private:

	AShooterPlayerState* GetShooterPlayerState() const;
	AShooterGameModeBase* GetShooterGameModeBase() const;
};
