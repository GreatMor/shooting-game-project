// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerHUDWidget.h"
#include "ShooterUtils.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Player/ShooterPlayerState.h"
#include "Components/ProgressBar.h"

 
bool UPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    return Super::Initialize();
}

float UPlayerHUDWidget::GetHealthPercent()
{
    const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.f;

    return HealthComponent->GetHealthPercent();
}

void UPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
    const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(Pawn);
    if (HealthComponent && !HealthComponent->OnHealthChange.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChange.AddUObject(this, &UPlayerHUDWidget::OnHeaalthChanged);
    }
    UpdateHealthBar();
}

bool UPlayerHUDWidget::GetWeaponUIDate(FWeaponUIDate &UIDate) const
{
    const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIDate(UIDate);
}

bool UPlayerHUDWidget::GetWeaponAmmoDate(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = ShooterUtils::GetShooterPLayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;
   
    return WeaponComponent->GetWeaponAmmoDate(AmmoData);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = ShooterUtils::GetShooterPLayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDeath();
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

UWeaponComponent* UPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    return WeaponComponent;
}

UHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    return HealthComponent;
}

void UPlayerHUDWidget::OnHeaalthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.f)
    {
        OnTakeDamage();
    }  
    UpdateHealthBar();
}

void UPlayerHUDWidget::UpdateHealthBar()
{
    if(HealtProgressBar)
    {
        HealtProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentVisibilityThreshold ? GoodColor : BadColor);
    }
}

int32 UPlayerHUDWidget::GetKills() const
{
    const auto Controller = GetOwningPlayer();
    if(!Controller) return 0;
        
    const auto PlayerStaet = Cast<AShooterPlayerState>(Controller->PlayerState);

    return PlayerStaet ? PlayerStaet->GetKillsNum() : 0;
}