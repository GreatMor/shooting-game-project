// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/CoreType.h"
#include "ShooterGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTER_API UShooterGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized()override;

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStateBox;

	UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStateRowWidgetClass;

private:
	void OnMatchStateChanged(EShooterMatchState State);
	void UpdatePlayeStaet();

	UFUNCTION()
    void OnResetLevel();
};
