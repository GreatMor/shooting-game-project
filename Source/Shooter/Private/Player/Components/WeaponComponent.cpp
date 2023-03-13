#include "Player/Components/WeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon/BaseGun.h"
#include "Animations/EquipAnimNotify.h"
#include "Animations/ReloadFinisedAnimNotify.h"
#include "GameFramework/Character.h"

constexpr static int32 WEAPONNUM = 2;

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}

void UWeaponComponent::Reload()
{
    ChangeClip();
}

void UWeaponComponent::StartFire()
{
    if (!CanFire()) return; 

    CurrentWeapon->StartFire();
}


bool UWeaponComponent::GetWeaponUIDate(FWeaponUIDate &UIDate) const 
{
    if (CurrentWeapon)
    {
        UIDate = CurrentWeapon->GetUIDate();
        return true;
    }
    else
    {
        return false;
    }
}

bool UWeaponComponent::GetWeaponAmmoDate(FAmmoData &AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoDate();
        return true;
    }
    else
    {
        return false;
    }
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    //checkf(Weapons.Num() == WEAPONNUM, TEXT("Bullets zero"))
    CurrentWeaponIndex = 0;
    SpawnWeapons();
    InitAnimatin();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;

    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();      
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!GetWorld() || !Character) return;

    for (auto OneWeaponClass : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ABaseGun>(OneWeaponClass.WeaponClass);
        if (!Weapon) continue;
        Weapon->OnClipsEmpty.AddUObject(this, &UWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }   
}

void UWeaponComponent::AttachWeaponToSocket(ABaseGun *Weapon, USceneComponent *SceneComponent,const FName& NameSockett)
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, NameSockett);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 && WeaponIndex >= Weapons.Num())
    {
        return;
    }
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    
    const auto CurrentWeaponDate = WeaponData.FindByPredicate([&](const FWeaponData &Data)//
                                    {return Data.WeaponClass == CurrentWeapon->GetClass(); //
    });
    
    CurrentRelodaAmiMontage = CurrentWeaponDate ? CurrentWeaponDate->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true; 
    PlayAnimMontage(EquipWeaponAnimMontage);
}

void UWeaponComponent::InitAnimatin()
{
  auto EquipFinishedNotify = FindNotifyByClass<UEquipAnimNotify>(EquipWeaponAnimMontage);
  if(EquipFinishedNotify)
  {
    EquipFinishedNotify->OnNotify.AddUObject(this, &UWeaponComponent::OnEquipFinished);
  }
  else
  {
      UE_LOG(LogTemp, Warning, TEXT("AnimNotify not found "));
      checkNoEntry();
  }

  for(auto OneWeapon : WeaponData)
  {
      auto ReloadFinishedNotify = FindNotifyByClass<UReloadFinisedAnimNotify>(OneWeapon.ReloadAnimMontage);
      if (!ReloadFinishedNotify) 
      {
          UE_LOG(LogTemp, Warning, TEXT("AnimNotify Reloade not found "));
          checkNoEntry();
      }
      ReloadFinishedNotify->OnNotify.AddUObject(this, &UWeaponComponent::OnReloadFinised);     
  }
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent *SkeletalMeshComponent)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || SkeletalMeshComponent != Character->GetMesh()) return;
    {
        EquipAnimInProgress = false;
    }    
}

void UWeaponComponent::OnReloadFinised(USkeletalMeshComponent *SkeletalMeshComponent)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || SkeletalMeshComponent != Character->GetMesh())
        return;    

      ReloadAnimInProgres = false;   
}

bool UWeaponComponent::CanFire()
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgres;
}

bool UWeaponComponent::CanEquip()
{
    return !EquipAnimInProgress && !ReloadAnimInProgres;
}

bool UWeaponComponent::CanReload()
{
    return CurrentWeapon//
           && !EquipAnimInProgress//
           && !ReloadAnimInProgres//
           && CurrentWeapon->CanReload();
}

void UWeaponComponent::OnEmptyClip(ABaseGun* AmmountAmptyWeapon)
{
    if (CurrentWeapon == AmmountAmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (const auto Weapon : Weapons)
        {
            if (Weapon == AmmountAmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
}

void UWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgres = true;
    PlayAnimMontage(CurrentRelodaAmiMontage);
}

void UWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage *AnimMontage)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)  return;

    Character->PlayAnimMontage(AnimMontage);
}

bool UWeaponComponent::TryToAddAmmo(TSubclassOf<ABaseGun> WeaponType, int32 ClipsAmount)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

bool UWeaponComponent::NeedAmmo(TSubclassOf<ABaseGun> WeaponType)
{
    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull();
        }
    }
    return false;
}


