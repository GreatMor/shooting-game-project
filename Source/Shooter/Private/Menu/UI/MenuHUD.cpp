// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuHUD.h"
#include "Menu/UI/MenuWidget.h"

void AMenuHUD::BeginPlay()
{
	const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	if(MenuWidget)
	{
      MenuWidget->AddToViewport();
	}
}
