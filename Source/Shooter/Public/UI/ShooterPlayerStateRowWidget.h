// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPlayerStateRowWidget.generated.h"

class UTextBlock;
class UImage;
UCLASS()
class SHOOTER_API UShooterPlayerStateRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayeName(const FText& Text);
	void SetKills(const FText& Text);
	void SetDeaths(const FText& Text);
	void SetPlayerTeam(const FText& Text);
	void SetPlayerIndicatorVisibikity(bool Visibiliti);
	void SetColorTeamImage(const FLinearColor& Color);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;	

	UPROPERTY(meta = (BindWidget))
	UImage* TeamImage;
};
