// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    auto PlayerTank = GetPlayerTank();

    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No controlled tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s is targetting %s"), *ControlledTank->GetName(), *PlayerTank->GetName());
    }
    
    UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (GetPlayerTank())
    {
        // TODO move towards player

        // Get Player pawn and aim(TODO) at their location
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}