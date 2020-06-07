// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::SpinTurret(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetRelativeRotation().ToString())
}