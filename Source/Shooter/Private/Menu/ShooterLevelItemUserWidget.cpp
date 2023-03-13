// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/ShooterLevelItemUserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UShooterLevelItemUserWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if(LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.DisplayLevelName));
	}

	if(LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void UShooterLevelItemUserWidget::SetSelectrd(bool IsSelected)
{
	if(FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden) ;
	}
}

void UShooterLevelItemUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UShooterLevelItemUserWidget::OnLevelItemClicked);
	}
}

void UShooterLevelItemUserWidget::OnLevelItemClicked()
{
	_OnLevelSelected.Broadcast(LevelData);	
}
