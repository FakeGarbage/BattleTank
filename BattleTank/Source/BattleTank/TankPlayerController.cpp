// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
    if (!ensure(GetPawn())) { return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; }
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FVector HitLocation; // Out Parameter

    if (GetSightRayLocation(HitLocation)) // TODO: make this raytrace
    {
        AimingComponent->AimAt(HitLocation);
    }
}


bool ATankPlayerController::GetSightRayLocation(FVector& HitLocation) const
{

    // Initialize viewport & view location variables
    int32 ViewportSizeX, ViewportSizeY;
    FVector LookDirection;

    // Get the size of the viewport and find screen location based on this
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    // Deproject crosshair location to world direction
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // line trace along look direction to see what you hit
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return false;
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe local method to tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}


void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    // Initialize view location vectors
    FVector WorldLocation; // to be discarded

    // Find location crosshair is pointing to in 3D space
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        OUT WorldLocation,
        OUT LookDirection
    );
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}