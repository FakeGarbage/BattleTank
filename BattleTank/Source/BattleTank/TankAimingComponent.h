// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declaration
class UTankBarrel;
class UTankTurret;


// Holds barrel/turret's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// set reference to barrel
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// set reference to turret
	void SetTurretReference(UTankTurret* TurretToSet);

	// ...
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// ...
	void MoveBarrel(FVector AimDirection);

	// ...
	void MoveTurret(FVector AimDirection);
};
