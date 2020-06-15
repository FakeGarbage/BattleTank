// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (ensure(PlayerTank))
    {
        auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
        // move towards player
        MoveToActor(PlayerTank, AcceptanceRadius);

        // Get Player pawn and aim(TODO) at their location
        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready (TODO: don't fire every frame)
        AimingComponent->FireTankProjectile();
    }
}