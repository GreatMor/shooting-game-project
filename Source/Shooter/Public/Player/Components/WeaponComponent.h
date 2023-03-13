#pragma once

#include "CoreMinimal.h"
#include "CoreType.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class USkeletalMeshComponent;
class ABaseGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	   

	UWeaponComponent();

    virtual void StartFire();
    virtual void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetWeaponUIDate(FWeaponUIDate& UIDate) const;

    bool GetWeaponAmmoDate(FAmmoData &AmmoData) const;

    UPROPERTY()
    ABaseGun* CurrentWeapon;

    UPROPERTY()
    TArray<ABaseGun*> Weapons;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;
   
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage *EquipWeaponAnimMontage;

    int32 CurrentWeaponIndex = 0;


    void PlayAnimMontage(UAnimMontage* AnimMontage);
    bool TryToAddAmmo(TSubclassOf<ABaseGun> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ABaseGun> WeaponType);
    bool CanFire();
    bool CanEquip();
    void EquipWeapon(int32 WeaponIndex);

protected:
	
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
   
private: 

    UPROPERTY()
    UAnimMontage* CurrentRelodaAmiMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgres = false;
	void SpawnWeapons();
    void AttachWeaponToSocket(ABaseGun *Weapon, USceneComponent *SceneComponent, const FName &NameSockett);
    
    void InitAnimatin();
    void OnEquipFinished(USkeletalMeshComponent *SkeletalMeshComponent);
    void OnReloadFinised(USkeletalMeshComponent *SkeletalMeshComponent);
    
    bool CanReload();

    void OnEmptyClip(ABaseGun* AmmountAmptyWeapon);
    void ChangeClip();

    template <typename T>
    T* FindNotifyByClass(UAnimSequenceBase* Animation) 
    {
      if(!Animation) return nullptr; 
      const auto NotifyEvents = Animation->Notifies;
      for (auto NotifyEvent : NotifyEvents) 
      {
        auto AnimNotify = Cast<T>(NotifyEvent.Notify);
        if (AnimNotify)
        {
          return AnimNotify;
        }
      }
      return nullptr;
    }
};


