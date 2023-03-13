// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameModeBase.h"
#include "CoreType.h"
#include "ShooterGameModeBase.generated.h"

class UCameraComponent;
class AAIController; 

UCLASS()
class SHOOTER_API AShooterGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AShooterGameModeBase();
    FOnMatchChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;

    void Killed(AController* KillerController, AController* VictimController);

    FGameData GetGameDate() const { return GameData; };
    int32 GetCurrentRound() const { return CurrentRound; };
    int32 GetCurrentTime() const { return RoundCountDown; };
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    void RespawmRequest(AController* Controller);

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController>AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn>AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FGameData GameData;

    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    // int32 GetKills() { return CurrentRound; };

private: 
    EShooterMatchState MatchState = EShooterMatchState::WaitingToStart;
    int32 CurrentRound = 1; 
    int32 RoundCountDown = 0.f;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DeterminClorByTeamID(int32 TeamID);
    void SetPlayerColoer(AController* Contoller);

    void LogPlayerInfo();

    void StartRespawn(AController* Controller);

    void GameOver();

    void  SetMatchStaet(EShooterMatchState State);
};
