// Fill out your copyright notice in the Description page of Project Settings.

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
	CurrentHealth = TotalHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("%f, %i"), DamageAmount, DamageToApply);

	return DamageToApply;
}


float ATank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)TotalHealth;
	UE_LOG (LogTemp, Warning, TEXT("%f"), (float)CurrentHealth / (float)TotalHealth);
}