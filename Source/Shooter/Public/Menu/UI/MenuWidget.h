// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreType.h"
#include "MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UShooterGameInstance;
class UShooterLevelItemUserWidget;
class USoundCue;

UCLASS()
class SHOOTER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* StartGameSound;

	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void OnLevelSelected(const FLevelData& Data);

private:

	UPROPERTY()
	TArray<UShooterLevelItemUserWidget*> LevelItemWidgets;
	
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();

	
	UShooterGameInstance* GetShooterGameInstance() const;

	 
	
};
