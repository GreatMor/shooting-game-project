// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CoreType.h"
#include "GameFramework/PlayerController.h"
#include "ShutterBasePlayerController.generated.h"

class UShooterRespawnComponent;

UCLASS()
class SHOOTER_API AShuterBasePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AShuterBasePlayerController();
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UShooterRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* aPawn) override;
    virtual void SetupInputComponent() override;
  
private:
    void OnMatchStateChanged(EShooterMatchState State);
    void OnPauseGame();
};
