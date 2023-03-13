// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "Shooter/ShooterGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameWidgets.Add(EShooterMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass));
    GameWidgets.Add(EShooterMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EShooterMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
    
    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidge = GameWidgetPair.Value;
        if(!GameWidge) continue;

        GameWidge->AddToViewport();
        GameWidge->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GetWorld())
    {
       const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
       if (GameMode)
       {
           GameMode->OnMatchStateChanged.AddUObject(this, &AGameHUD::OnMatchStateChanged);
       }
    }
}

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();
   // DrawCrossHair();
}

void AGameHUD::DrawCrossHair()
{
   
    const TInterval<float>Cener(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.f;
    const float LineThickness = 2.f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Cener.Min - HalfLineSize, Cener.Max, Cener.Min + HalfLineSize, Cener.Max, LineColor, LineThickness);
    DrawLine(Cener.Min, Cener.Max - HalfLineSize, Cener.Min, Cener.Max + HalfLineSize, LineColor, LineThickness);
}

void AGameHUD::OnMatchStateChanged(EShooterMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    UE_LOG(LogTemp, Warning, TEXT("Staet game changed %s"), *UEnum::GetValueAsString(State));
}
