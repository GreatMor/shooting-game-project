// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"


bool UShooterPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (CleatrPauseButton)
    {
        CleatrPauseButton->OnClicked.AddDynamic(this, &UShooterPauseWidget::OnClearPause);
    }
    return InitStatus;
}

void UShooterPauseWidget::OnClearPause()
{
    if (GetWorld() || GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
    }
}
