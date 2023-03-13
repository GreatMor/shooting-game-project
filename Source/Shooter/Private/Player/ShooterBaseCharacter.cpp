// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterBaseCharacter.h"
#include "Player/Components/ShuterMovementComponent.h"
#include "Player/Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponComponent.h"

// Sets default values
AShooterBaseCharacter::AShooterBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<UShuterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
}
   

// Called when the game starts or when spawned
void AShooterBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
   
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChange(HealthComponent->GetHealth(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &AShooterBaseCharacter::OnDeath);
    HealthComponent->OnHealthChange.AddUObject(this, &AShooterBaseCharacter::OnHealthChange);
    LandedDelegate.AddDynamic(this, &AShooterBaseCharacter::OnGroundLanded);

}

// Called every frame
void AShooterBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AShooterBaseCharacter::SetPlayerColor(FLinearColor Color)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInstance) return;

    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

float AShooterBaseCharacter::GetMovementDirectiob()
{
    if(GetVelocity().IsZero())
        return 0.f;
    
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);   
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AShooterBaseCharacter::OnDeath()
{
    WeaponComponent->StopFire();
    PlayAnimMontage(AnimDeath);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.f);
   
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void AShooterBaseCharacter::OnHealthChange(float Health, float HealthDelta)
{
    
}

bool AShooterBaseCharacter::IsRunning() const
{
    return false;
}


void AShooterBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamag = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamag, FDamageEvent{}, nullptr, nullptr);
}



