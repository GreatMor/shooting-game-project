// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterPlayerStateRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UShooterPlayerStateRowWidget::SetPlayeName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UShooterPlayerStateRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void UShooterPlayerStateRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void UShooterPlayerStateRowWidget::SetPlayerTeam(const FText& Text)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void UShooterPlayerStateRowWidget::SetPlayerIndicatorVisibikity(bool Visibiliti)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visibiliti ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UShooterPlayerStateRowWidget::SetColorTeamImage(const FLinearColor& Color)
{
	if(!TeamImage) return;

	TeamImage->SetColorAndOpacity(Color);
}
