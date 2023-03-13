#include "Weapon/BaseGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Controller.h"

ABaseGun::ABaseGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("body");
    SetRootComponent(WeaponMesh);
}

void ABaseGun::StartFire()
{
}

void ABaseGun::StopFire()
{  
}

bool ABaseGun::IsAmmoFull()
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
   

    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets zero"))
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips zero"))
    CurrentAmmo = DefaultAmmo; 
}

void ABaseGun::MakeShot()
{ 
}

bool ABaseGun::GetPlayerViewPoint(FVector& ViewLocatio, FRotator& ViewRotation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if(!Character) return false;

    if (Character->IsPlayerControlled())
    {
        const auto Controller = Character->GetController<APlayerController>();
        if (!Controller) return false;

        Controller->GetPlayerViewPoint(ViewLocatio, ViewRotation);
    }
    else
    {
        ViewLocatio = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzelSoclet);
    }
   
    return true;
}

FVector ABaseGun::GetMuzzleWorldLocation() const 
{
    return WeaponMesh->GetSocketLocation(MuzzelSoclet);
}

bool ABaseGun::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocatio;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocatio, ViewRotation)) return false;

    TraceStart = ViewLocatio;
   
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * MaxTraceDistance;
    return true;
}

void ABaseGun::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{   
    if(!GetWorld()) return;

    FCollisionQueryParams CollisionParams;

    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;
  
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ABaseGun::DecreaseAmmo()
{
    if(CurrentAmmo.Bullets == 0)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Clip is empty"));
        return;
    }
    CurrentAmmo.Bullets--;
    
    if(IsClipsEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipsEmpty.Broadcast(this);
    }
}

bool ABaseGun::IsAmmoEmpty()
{
    bool b_IsEmpty = !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipsEmpty();   
    return b_IsEmpty;
}

bool ABaseGun::IsClipsEmpty()
{   
    //UE_LOG(LogTemp, Warning, TEXT("Bullets %i" ), CurrentAmmo.Bullets);
   return CurrentAmmo.Bullets == 0;
}

void ABaseGun::ChangeClip()
{  
   if(!CurrentAmmo.Infinite)
   {
       if(CurrentAmmo.Clips == 0)
       {
           //UE_LOG(LogTemp, Warning, TEXT("Error Bullets"));
           return;
       }
       CurrentAmmo.Clips--;
   }
   CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ABaseGun::CanReload()
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ABaseGun::TryToAddAmmo(int32 ClipsAmount)
{
    if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if (IsAmmoEmpty())
    {
        CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipsEmpty.Broadcast(this);
    }
    else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
    {   
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
        }
        else
        {
            CurrentAmmo.Clips = NextClipsAmount;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
    return true;
}

void ABaseGun::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infitite " : FString::FromInt(CurrentAmmo.Clips);
   // UE_LOG(LogTemp, Warning, TEXT(" % s"), *AmmoInfo);
}

UNiagaraComponent* ABaseGun::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX//
        ,WeaponMesh   //
        ,MuzzelSoclet   //
        ,FVector::ZeroVector//
        ,FRotator::ZeroRotator //
        ,EAttachLocation::SnapToTarget //
        ,true//
        );
}



