
#include "Weapon/RifleWeapon.h"
#include "Engine/World.h"
#include "NiagaraComponent.h"
#include "DrawDebugHelpers.h"

#include "NiagaraFunctionLibrary.h"
#include "FXComponents/ShooterFXSystemComponent.h"


ARifleWeapon::ARifleWeapon()
{
    FXComponent = CreateDefaultSubobject<UShooterFXSystemComponent>("FXSystemComponent");
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(FXComponent);
}

void ARifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShort, true);
    MakeShot();
}

void ARifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzleFXVisibility(false);
}

void ARifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }
       
   /* const auto Controller = GetPlayerController();
    if (!Controller)
        return;*/

    FVector TraceStart, EndTrace;
    if (!GetTraceData(TraceStart, EndTrace)) return;

    FHitResult HitResult;

    MakeHit(HitResult, TraceStart, EndTrace);

    FVector TraceFXEnd = EndTrace;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        FXComponent->PlayImpactFX(HitResult);     
    }

    SpawnTraceFX(GetMuzzleWorldLocation(),TraceFXEnd);
    DecreaseAmmo();
}


void ARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor)
        return;

    DamageActor->TakeDamage(DamagAmount, FDamageEvent{}, GetController(), this);
}

void ARifleWeapon::InitMuzzleFX()
{
    if(!MuzzleFXComponent)
        MuzzleFXComponent = SpawnMuzzleFX();

    SetMuzleFXVisibility(true);
}

void ARifleWeapon::SetMuzleFXVisibility(bool Visible)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(Visible);
        MuzzleFXComponent->SetVisibility(Visible);
    }
}

bool ARifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    FVector ViewLocatio;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocatio, ViewRotation))
        return false;

    TraceStart = ViewLocatio;
    const auto HalfeRad = FMath::DegreesToRadians(BulletSpret);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfeRad);
    TraceEnd = TraceStart + ShootDirection * MaxTraceDistance;
    return true;
}


void ARifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart, FRotator::ZeroRotator);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ARifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}


