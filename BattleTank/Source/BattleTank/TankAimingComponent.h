// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

// forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


// Holds barrel/turret's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// ...
	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


public:	
	// ...
	UFUNCTION(BluePrintCallable, Category = "Input")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// ...
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireTankProjectile();

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	// ...
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// ...
	void AimAt(FVector HitLocation);

	// ...
	void MoveBarrel(FVector AimDirection);

	// ...
	void MoveTurret(FVector AimDirection);
};
