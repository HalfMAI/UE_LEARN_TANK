// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float CrossHairLocX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairLocY = 0.333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCosshair();
	bool GetSightRayHitLoaction(OUT FVector& out_HitLocation) const;
	bool GetLookVectorHitLocation(FVector& LookLocation, FVector& LookDirection, OUT FVector& out_HitLocation) const;
	bool GetCossHairLookLocationAndDirection(OUT FVector& tmpCamWorldLocation, OUT FVector& tmpCamWorldDirection) const;
};
