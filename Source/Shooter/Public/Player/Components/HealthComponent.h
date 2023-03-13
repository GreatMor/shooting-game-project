// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreType.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    float GetHealth()const { return Health; };

    UFUNCTION(BlueprintCallable)
    bool IsDeath() const {return Health <= 0.0f;}
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetHealthPercent() const  { return Health/MaxHealth; };

    bool TryToAddHealth(float AmmountHealth);

    FOnDeath OnDeath;
    FOnHealthChange OnHealthChange;

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
private:
    UFUNCTION()
   void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMax = "1000", ClampMin = "0"))
    float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHealth = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealtDelay = 3;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
     float HealthModifier = 5;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
     float HealtUpdateTiame = 0.4;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
     TSubclassOf<UCameraShakeBase>CameraShake;
         
private:
    float Health = 0.f;

    FTimerHandle HealthTimerHandle;

    void HealthUpdate();

    bool IsHelthFull() const;

    void SetHealth(float AmmountHealth);
    void PlayCameraShake();

    void Killed(AController* KillerController);
};
