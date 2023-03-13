// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterGoToMenurWidget.h"
#include "ShooterGameInstance.h"
#include "KisMet/GamePlayStatics.h"
#include "Components/Button.h"

void UShooterGoToMenurWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (OpenMainMenuButton)
    {
        OpenMainMenuButton->OnClicked.AddDynamic(this, &UShooterGoToMenurWidget::OnOpenMainMenu);
    }
}

void UShooterGoToMenurWidget::OnOpenMainMenu()
{
    if (!GetWorld()) return;

    const auto ShooterGameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
    if (!ShooterGameInstance) return;

    if (ShooterGameInstance->GetLavelsData().Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Level none"))
            return;
    }
  
    UGameplayStatics::OpenLevel(this, ShooterGameInstance->GetMenuLevelName());
}


