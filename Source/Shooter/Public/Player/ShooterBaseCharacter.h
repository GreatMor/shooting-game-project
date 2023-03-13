// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShooterBaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;

UCLASS()
class SHOOTER_API AShooterBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;    
    
    void Fire();    
    AShooterBaseCharacter(const FObjectInitializer &ObjInit);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirectiob();
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    void SetPlayerColor(FLinearColor color);

private:
  
    
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
 
 protected:
    virtual void OnHealthChange(float Healt, float HealthDelta);
    virtual void BeginPlay() override;
    virtual void OnDeath();
   
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWeaponComponent *WeaponComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* AnimDeath;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.f, 100.f); 

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";


};
