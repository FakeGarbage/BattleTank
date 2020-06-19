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
	Reloading,
	NoAmmo
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
	// ...
	double LastFireTime = 0;

	// ...
	FVector AimDirection;

	// Sets default values for this component's properties
	UTankAimingComponent();

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	// ...
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// ...
	void MoveBarrel(FVector TankAimDirection);

	// ...
	void MoveTurret(FVector TankAimDirection);

	// ...
	bool IsBarrelMoving();

	// ...
	virtual void BeginPlay();

	// ...
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


public:
	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 5;

	// ...
	UFUNCTION(BluePrintCallable, Category = "Input")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// ...
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireTankProjectile();

	// ...
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 AmmoRemaining() const;

	// ...
	void AimAt(FVector HitLocation);

	// ...
	EFiringState GetFiringState() const;
};
