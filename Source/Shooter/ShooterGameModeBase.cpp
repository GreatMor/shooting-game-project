// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"
#include "ShutterBasePlayerController.h"
#include "ShooterBaseCharacter.h"
#include "ShooterPlayerState.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterRespawnComponent.h"
#include "GameFramework/PlayerState.h"
#include "UI/GameHUD.h"
#include "EngineUtils.h"

AShooterGameModeBase::AShooterGameModeBase()
{
    DefaultPawnClass = AShooterBaseCharacter::StaticClass();
    PlayerControllerClass = AShuterBasePlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
    PlayerStateClass = AShooterPlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
    Super::StartPlay();
    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();
    SetMatchStaet(EShooterMatchState::InProgress);

}

void AShooterGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlyerState = KillerController ? Cast<AShooterPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlyerState = VictimController ? Cast<AShooterPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlyerState)
    {
        KillerPlyerState->AddKill();
    }

    if (VictimPlyerState)
    {
        VictimPlyerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void AShooterGameModeBase::RespawmRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool AShooterGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchStaet(EShooterMatchState::Pause);
    }
    
    return PauseSet;
}

bool AShooterGameModeBase::ClearPause()
{
    const auto PauseClear = Super::ClearPause();
    if (PauseClear)
    {
        SetMatchStaet(EShooterMatchState::InProgress);
    }
    return PauseClear;
}

UClass* AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(AIController);
    }
}

void AShooterGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShooterGameModeBase::GameTimerUpdate, 1.f, true);
}

void AShooterGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogTemp, Warning, TEXT("Time: %i / Round %i/%i"),RoundCountDown, CurrentRound, GameData.RoundNum)
   
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if(CurrentRound + 1 <= GameData.RoundNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void AShooterGameModeBase::ResetPlayers()
{
    if(!GetWorld()) return; 

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColoer(Controller);
}

void AShooterGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
       const auto Controller =  It->Get();
       if(!Controller) continue;
      
       const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
       if(!PlayerState) continue;

       PlayerState->SetTeamID(TeamID);
       PlayerState->SetTeamColor(DeterminClorByTeamID(TeamID));
       PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
       SetPlayerColoer(Controller);

       TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AShooterGameModeBase::DeterminClorByTeamID(int32 TeamID)
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    else
    {
        return GameData.DefaultColor;
    }
}

void AShooterGameModeBase::SetPlayerColoer(AController* Contoller)
{
    if(!Contoller) return;

    const auto Character = Cast<AShooterBaseCharacter>(Contoller->GetPawn());
    if(!Character) return; 

    const auto PlayerState = Cast<AShooterPlayerState>(Contoller->PlayerState);
    if(!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AShooterGameModeBase::LogPlayerInfo()
{
    if (!GetWorld()) return;
      
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void AShooterGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnComponent = ShooterUtils::GetShooterPLayerComponent<UShooterRespawnComponent>(Controller);
    if(!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AShooterGameModeBase::GameOver()
{
    UE_LOG(LogTemp, Warning, TEXT(" === Game Over === "))
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    SetMatchStaet(EShooterMatchState::GameOver);
}

void AShooterGameModeBase::SetMatchStaet(EShooterMatchState State)
{
    if(MatchState == State) return; 

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
