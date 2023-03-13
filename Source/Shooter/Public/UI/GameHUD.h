// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CoreType.h"
#include "GameHUD.generated.h"

class UPlayerHUDWidget;
class UProgressBar;
UCLASS() class SHOOTER_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override; 
	virtual void DrawHUD() override;
    void DrawCrossHair();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	void OnMatchStateChanged(EShooterMatchState State);

	UPROPERTY(meta =(BindWidget))
	UProgressBar* HealthBar;

private:
	UPROPERTY()
	TMap<EShooterMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr; 
};
