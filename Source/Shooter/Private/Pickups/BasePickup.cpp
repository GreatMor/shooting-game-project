// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SetRootComponent(CollisionComponent);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
	GeneratedRotationYaw();
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("OtherActor %s"),*OtherActor->GetName());
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}	
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.f,RotationYaw, 0.f));
}

bool ABasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawTumerHandele);
}

bool ABasePickup::GivePickupTo(APawn* Pawn)
{
	return false;
}

void ABasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	if(GetRootComponent())
	GetRootComponent()->SetVisibility(false, true);	
	GetWorldTimerManager().SetTimer(RespawTumerHandele, this, &ABasePickup::Respawn, RespawTime);
}

void ABasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);

	GeneratedRotationYaw();

	if (GetRootComponent())
		GetRootComponent()->SetVisibility(true, true);
}

void ABasePickup::GeneratedRotationYaw()
{
	float Direction = FMath::RandBool() ? 1.f : -1.f;
	RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}

