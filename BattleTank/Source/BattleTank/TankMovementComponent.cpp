// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    UE_LOG(LogTemp, Warning, TEXT("%f"), Throw);
    // TODO prevent double speed
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // Don't need to call super as we're replacing functionality
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);

    auto AlignThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(AlignThrow);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    // TODO prevent double speed
}


void UTankMovementComponent::IntendTurnLeft(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(-Throw);
    // TODO prevent double speed
}