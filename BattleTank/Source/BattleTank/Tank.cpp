// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *HitLocation.ToString());
}


void ATank::FireTankProjectile()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		// Spawn Projectile at socket location on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}