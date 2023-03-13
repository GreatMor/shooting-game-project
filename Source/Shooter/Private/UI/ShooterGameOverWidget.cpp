// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterGameOverWidget.h"
#include "Shooter/ShooterGameModeBase.h"
#include "Components/VerticalBox.h"
#include "Player/ShooterPlayerState.h"
#include "ShooterUtils.h"
#include "UI/ShooterPlayerStateRowWidget.h"
#include "KisMet/GamePlayStatics.h"
#include "Components/Button.h"
#include "ShooterGameInstance.h"

void UShooterGameOverWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameModeBase = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameModeBase)
        {
            GameModeBase->OnMatchStateChanged.AddUObject(this, &UShooterGameOverWidget::OnMatchStateChanged);
        }
        if(ResetLevelButton)
        {
            ResetLevelButton->OnClicked.AddDynamic(this, &UShooterGameOverWidget::OnResetLevel);
        }      
    }
}

void UShooterGameOverWidget::OnMatchStateChanged(EShooterMatchState State)
{
    if (State == EShooterMatchState::GameOver)
    {
        UpdatePlayeStaet();
    }
}

void UShooterGameOverWidget::UpdatePlayeStaet()
{
    if(!GetWorld() || !PlayerStateBox) return;

    PlayerStateBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto  Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStateRowWidget = CreateWidget<UShooterPlayerStateRowWidget>(GetWorld(), PlayerStateRowWidgetClass);
        if(!PlayerStateRowWidget) continue;

        PlayerStateRowWidget->SetPlayeName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStateRowWidget->SetKills(ShooterUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStateRowWidget->SetDeaths(ShooterUtils::TextFromInt(PlayerState->GetDeathNum()));
        PlayerStateRowWidget->SetPlayerTeam(ShooterUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStateRowWidget->SetPlayerIndicatorVisibikity(Controller->IsPlayerController());
        PlayerStateRowWidget->SetColorTeamImage(PlayerState->GetTeamColor());

        PlayerStateBox->AddChild(PlayerStateRowWidget);
    }
}

void UShooterGameOverWidget::OnResetLevel()
{ 
    const FString CurrentNameLavel = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentNameLavel));
}


