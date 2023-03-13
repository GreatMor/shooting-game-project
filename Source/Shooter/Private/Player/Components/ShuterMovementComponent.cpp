// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/ShuterMovementComponent.h"
#include "Player/ShooterBaseCharacter.h"

float UShuterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AShooterBaseCharacter *Player = Cast<AShooterBaseCharacter>(GetPawnOwner());  
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
