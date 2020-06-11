// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s throttle is %f"), *Name, Throttle);

    // TODO clamp throttle value
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxThrottle;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);  
}