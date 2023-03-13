// Fill out your copyright notice in the Description page of Project Settings.


#include "FXComponents/ShooterFXSystemComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


UShooterFXSystemComponent::UShooterFXSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
};

void UShooterFXSystemComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
		ImpactData.NiagaraEffect,//
		Hit.ImpactPoint,//
		Hit.ImpactNormal.Rotation()//
		);

	//UDecalComponent* UGameplayStatics::SpawnDecalAtLocation(const UObject * WorldContextObject, class UMaterialInterface* DecalMaterial, FVector DecalSize, FVector Location, FRotator Rotation, float LifeSpan)

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(), //
		ImpactData.DecalData.Materisl,//
		ImpactData.DecalData.Size, //
		Hit.ImpactPoint, //
		Hit.Normal.Rotation(), //
		ImpactData.DecalData.LifrTime // 
		);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifrTime, ImpactData.DecalData.FadeOutTime);
	}
}
