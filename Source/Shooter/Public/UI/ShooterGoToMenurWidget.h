// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterGoToMenurWidget.generated.h"

class UButton;

UCLASS()
class SHOOTER_API UShooterGoToMenurWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized()override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* OpenMainMenuButton;

private:

	UFUNCTION()
	void OnOpenMainMenu();
};
