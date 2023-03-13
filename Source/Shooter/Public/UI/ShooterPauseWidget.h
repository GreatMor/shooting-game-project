// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTER_API UShooterPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	
	UPROPERTY(meta = (BindWidget))
	UButton* CleatrPauseButton;

private:

	UFUNCTION()
	void OnClearPause();
	
};
