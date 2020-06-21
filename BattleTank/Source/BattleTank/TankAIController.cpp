// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

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

        if (AimingComponent->GetFiringState() == EFiringState::Locked)
        {
            AimingComponent->FireTankProjectile();
        }
    }
}


void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe local method to tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}


void ATankAIController::OnPossessedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Received"));
}