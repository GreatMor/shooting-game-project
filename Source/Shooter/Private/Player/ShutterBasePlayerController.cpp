// Fill out your copyright notice in the Description page of Project Settings.

#include "ShutterBasePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Shooter/ShooterGameModeBase.h"


AShuterBasePlayerController::AShuterBasePlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("RespawnComponent");
}

void AShuterBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AShuterBasePlayerController::OnMatchStateChanged);
		}
	}
}

void AShuterBasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	OnNewPawn.Broadcast(aPawn);
}

void AShuterBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AShuterBasePlayerController::OnPauseGame);
}

void AShuterBasePlayerController::OnMatchStateChanged(EShooterMatchState State)
{
	if (State == EShooterMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void AShuterBasePlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->SetPause(this);
}
