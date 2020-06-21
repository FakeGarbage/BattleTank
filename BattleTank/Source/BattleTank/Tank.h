// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	FTankDelegate OnDeath;

	// called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// returns current health as percentage of starting health
	UFUNCTION(BlueprintPure, Category = "health")
	float GetHealthPercent();

private:
	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TotalHealth = 100;

	// ...
	int32 CurrentHealth = TotalHealth;
};