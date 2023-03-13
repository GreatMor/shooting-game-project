// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreType.h"
#include "PlayerHUDWidget.generated.h"

class UWeaponComponent;
class UHealthComponent;
class UProgressBar;

UCLASS()
class SHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealtProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentVisibilityThreshold = 0.8f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

    UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	void OnNewPawn(APawn* Pawn);

    UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIDate(FWeaponUIDate &UIDate) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoDate(FAmmoData &AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetKills() const;

protected:

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;*/

	virtual bool Initialize() override;

private: 
	UWeaponComponent* GetWeaponComponent() const;
	UHealthComponent* GetHealthComponent() const;
	void OnHeaalthChanged(float Health, float HealthDelta);

	void UpdateHealthBar();
};
