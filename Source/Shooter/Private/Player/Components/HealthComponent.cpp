// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Dev/IceDamageType.h"
#include "Dev/FireDamageType.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/Controller.h"
#include "Shooter/ShooterGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
} 
bool UHealthComponent::TryToAddHealth(float AmmountHealth)
{
    if (IsDeath() && IsHelthFull()) return false;
   
    SetHealth(Health + AmmountHealth);
    return true;
}
// Called when the game starts
void UHealthComponent::BeginPlay()
{    
    Super::BeginPlay();
    Health = MaxHealth;

    OnHealthChange.Broadcast(Health, 0.f);

    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
       ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
    }    
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                                    class AController* InstigatedBy, AActor* DamageCauser )
{
    if (Damage <= 0 || IsDeath() || !GetWorld()) return;

    //Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth );
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
         
    if(IsDeath())
    {   
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if(AutoHealth && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this,&UHealthComponent::HealthUpdate, HealtUpdateTiame,true, HealtDelay);
    }

    PlayCameraShake(); 
}

void UHealthComponent::HealthUpdate()
{    
     //OnHealthChange.Broadcast(Health);  
    SetHealth(Health + HealthModifier);
    if(IsHelthFull() && GetWorld())
    {
      GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    }
}

bool UHealthComponent::IsHelthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UHealthComponent::SetHealth(float AmmountHealth)
{
    const auto NextHealth = FMath::Clamp(AmmountHealth, 0.f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    Health = NextHealth;//FMath::Min(Health + AmmoyntHealth, MaxHealth);

    OnHealthChange.Broadcast(Health, HealthDelta);
}

void UHealthComponent::PlayCameraShake()
{
    if(IsDeath()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if(!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if(!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}

void UHealthComponent::Killed(AController* KillerController)
{
    if(!GetWorld()) return;

    const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}
