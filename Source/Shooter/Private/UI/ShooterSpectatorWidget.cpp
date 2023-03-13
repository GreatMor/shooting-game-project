// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterSpectatorWidget.h"
#include "ShooterUtils.h"
#include "Components/ShooterRespawnComponent.h"

bool UShooterSpectatorWidget::GetRespawnTime(int32& CountDownTime)
{
	const auto RespawComponent = ShooterUtils::GetShooterPLayerComponent<UShooterRespawnComponent>(GetOwningPlayer());

	if(!RespawComponent || !RespawComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawComponent->GetRespawnCountdown();
	return true;
}
