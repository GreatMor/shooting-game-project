#include "Player/Components/ShooterRespawnComponent.h"
#include "Shooter/ShooterGameModeBase.h"

UShooterRespawnComponent::UShooterRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterRespawnComponent::Respawn(int32 RespawnTime)
{
	if(!GetWorld()) return;
	RespawnCountdown = RespawnTime;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UShooterRespawnComponent::RespawnTimerUpdate, 1.f, true);
}

bool UShooterRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UShooterRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountdown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMode) return;

		GameMode->RespawmRequest(Cast<AController>(GetOwner()));
	}
}
