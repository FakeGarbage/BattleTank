// Fill out your copyright notice in the Description page of Project Settings.

#include "tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (PlayerTank)
    {
        // move towards player
        MoveToActor(PlayerTank, AcceptanceRadius);

        // Get Player pawn and aim(TODO) at their location
        Cast<ATank>(GetPawn())->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready (TODO: don't fire every frame)
        Cast<ATank>(GetPawn())->FireTankProjectile();
    }
}