// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No controlled tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *ControlledTank->GetName());
    }
    
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return;}

    FVector HitLocation; // Out Parameter

    if (GetSightRayLocation(HitLocation)) // TODO: make this raytrace
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // get world location thru crosshair
        // if it hits landscape
            // tell controlled tankt to aim at this point
    }
}

bool ATankPlayerController::GetSightRayLocation(FVector& HitLocation) const
{
    OUT HitLocation = FVector(1.0);
    return true;
    // if raytrace from HitLocation hits landscape
        // return true
    // else
        // return false
}