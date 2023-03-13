// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameDataWidget.h"
#include "Player/ShooterPlayerState.h"
#include "Shooter/ShooterGameModeBase.h"


int32 UGameDataWidget::GetCurrentRound() const
{
    const auto ShooterGameModeBase = GetShooterGameModeBase();
    return ShooterGameModeBase ? ShooterGameModeBase->GetCurrentRound() : 0;
}

int32 UGameDataWidget::GetTotalRound() const
{
    const auto ShooterGameModeBase = GetShooterGameModeBase();
    return ShooterGameModeBase ? ShooterGameModeBase->GetGameDate().RoundNum : 0;
}

int32 UGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto ShooterGameModeBase = GetShooterGameModeBase();
    return ShooterGameModeBase ? ShooterGameModeBase->GetCurrentTime() : 0;
}

AShooterPlayerState* UGameDataWidget::GetShooterPlayerState() const
{
    return GetOwningPlayer() ? Cast<AShooterPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}

AShooterGameModeBase* UGameDataWidget::GetShooterGameModeBase() const
{
    return GetWorld() ? Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
