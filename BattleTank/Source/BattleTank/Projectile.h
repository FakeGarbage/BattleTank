// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// forward declaration
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

private:
	void OnTimerExpire();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// ...
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.f;

	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20.f;

	// ...
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* CollisionMesh = nullptr;

	// ...
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* LaunchParticle = nullptr;

	// ...
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* ImpactParticle = nullptr;

	// ...
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent* ImpactForce = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// ...
	void LaunchProjectile(float Speed);

};
