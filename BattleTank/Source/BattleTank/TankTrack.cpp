// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    // ...
}


void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // Drive tracks
    DriveTrack();
    // Apply sideways force
    ApplySidewaysForce();
    // reset throttle
    CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
    // work out required accel this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectedAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

    // calc and apply sideways force
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectedAcceleration) / 2; // two tracks

    TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}


void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxThrottle;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);  
}