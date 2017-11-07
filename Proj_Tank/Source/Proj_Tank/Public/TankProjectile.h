// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "TankProjectile.generated.h"

UCLASS()
class PROJ_TANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float LaunchSpeed) const;

	UStaticMeshComponent* GetCollisionCom() const;
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnDestoryTimerCalled();


private:
	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	float DestroyDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	float ProjectileDamage = 1000.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionRadialForceComponent = nullptr;

	UProjectileMovementComponent* TankProjectileMC = nullptr;
};
