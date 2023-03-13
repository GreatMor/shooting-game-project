// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoreType.h"
#include "ShooterGameInstance.generated.h"

UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartUpLevel() const {return StartupLevel;}
	FName GetMenuLevelName() const { return StartupLevelMenu; }
	void SetStartUpLevelName(const FLevelData& Data) { StartupLevel = Data; }

	TArray<FLevelData> GetLavelsData() const {return LevelsData;}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData>LevelsData;

//UPROPERTY(EditDefaultsOnly, Category = "Game")
	

private:
	FLevelData StartupLevel;	
	FName StartupLevelMenu = "MenuLevel";
};
