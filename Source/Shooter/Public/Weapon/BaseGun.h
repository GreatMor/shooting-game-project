// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreType.h"
#include "BaseGun.generated.h"

class USkeletalMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTER_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseGun();

	FOnClipsEmptySignature OnClipsEmpty;

	virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload();
	bool IsAmmoFull();

	FWeaponUIDate GetUIDate() const { return UIDate; }
    FAmmoData GetAmmoDate() const { return CurrentAmmo; }
	bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float MaxTraceDistance = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamagAmount = 10.f;   

	UPROPERTY()
	FName MuzzelSoclet = "MuzzleFlashSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIDate UIDate; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FAmmoData CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

 protected:	

	virtual void BeginPlay() override;
    virtual void MakeShot();
 
    bool GetPlayerViewPoint(FVector &ViewLocatio, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    virtual bool GetTraceData(FVector& Start, FVector& End) const;
    void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd) const;
    void DecreaseAmmo();
   
    bool IsClipsEmpty();    
    void LogAmmo();  	
	UNiagaraComponent* SpawnMuzzleFX();
};
