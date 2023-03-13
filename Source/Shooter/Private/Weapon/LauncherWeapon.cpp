// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/CPPProjectile.h"

void ALauncherWeapon::StartFire()
{
    MakeShot();
}

void ALauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart, EndTrace;
    if (!GetTraceData(TraceStart, EndTrace))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, EndTrace);
    
    const FVector EndPoin = HitResult.bBlockingHit ? HitResult.ImpactPoint : EndTrace;
    const FVector Directin = (EndPoin - GetMuzzleWorldLocation()).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ACPPProjectile* Projectile = GetWorld()->SpawnActorDeferred<ACPPProjectile>(ProjectileClass,SpawnTransform);
    if(Projectile)
    {
        Projectile->SetShotDirection(Directin);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
}
