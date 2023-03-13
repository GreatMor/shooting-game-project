// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreType.h"
#include "ShooterFXSystemComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS()
class SHOOTER_API UShooterFXSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	UShooterFXSystemComponent();

public:

	void PlayImpactFX(const FHitResult& Hit);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
