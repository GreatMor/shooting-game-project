// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"

//#include "Math/UnrealMathUtility.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
	if(!HealtProgressBar) return;

	const auto HealthBarVisivility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) //
											? ESlateVisibility::Hidden //
											: ESlateVisibility::Visible;

	HealtProgressBar->SetVisibility(HealthBarVisivility);

	const auto HealthColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealtProgressBar->SetFillColorAndOpacity(HealthColor);

	HealtProgressBar->SetPercent(Percent);
}
