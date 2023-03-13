// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Menu/ShooterLevelItemUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"


void UMenuWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

	if(StartGameButton) 
	{
        StartGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
    }

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

void UMenuWidget::OnStartGame() 
{
	const auto GameInstance = GetShooterGameInstance();
	if (!GameInstance) return;

	UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
	GetWorld()->DeltaTimeSeconds = 2;
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartUpLevel().LevelName);
}

void UMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMenuWidget::InitLevelItems()
{	
	const auto GameInstance = GetShooterGameInstance();
	if(!GameInstance) return; 

	//checkf(GameInstance->GetLavelsData.Num() !=0, TEXT("Error levels not found "));

	if(!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for(auto LevelData : GameInstance->GetLavelsData())
	{
		const auto LecelItemWidget = CreateWidget<UShooterLevelItemUserWidget>(GetWorld(), LevelItemWidgetClass);
		if(!LecelItemWidget) continue;

		LecelItemWidget->SetLevelData(LevelData);
		LecelItemWidget->_OnLevelSelected.AddUObject(this, &UMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LecelItemWidget);
		LevelItemWidgets.Add(LecelItemWidget);
	}

	if(GameInstance->GetStartUpLevel().LevelName.IsNone())
	{
		OnLevelSelected(GameInstance->GetLavelsData()[0]);
	}
	else
	{
		OnLevelSelected(GameInstance->GetStartUpLevel());
	}
}

void UMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto GameInstance = GetShooterGameInstance();
	if (!GameInstance) return;
	
	GameInstance->SetStartUpLevelName(Data);
	
	for(auto LevelItemWidget: LevelItemWidgets)
	{
		const auto IsSelected = Data.DisplayLevelName == LevelItemWidget->GetLevelData().LevelName;
		LevelItemWidget->SetSelectrd(IsSelected);
	}
}

UShooterGameInstance* UMenuWidget::GetShooterGameInstance() const
{
	if(!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UShooterGameInstance>();
}
