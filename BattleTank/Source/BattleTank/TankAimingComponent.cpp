// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// so that we fire after initial reload
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// TODO: handle aiming and locked states
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}


void UTankAimingComponent::FireTankProjectile()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (ensure(Barrel) && ensure(ProjectileBlueprint))
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
}


void UTankAimingComponent::MoveBarrel(FVector TankAimDirection)
{
	// get the unit vector for the player's crosshair location and turn that into a pitch/yaw/roll
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = TankAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
}


void UTankAimingComponent::MoveTurret(FVector TankAimDirection)
{
	// get the unit vector for the player's crosshair location and turn that into a pitch/yaw/roll
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = TankAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->SpinTurret(DeltaRotator.Yaw);
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelDirection = Barrel->GetForwardVector();
	
	return !BarrelDirection.Equals(AimDirection, 0.01f);
}