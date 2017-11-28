// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
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
	float CrossHairLocY = 0.4f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

public:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossedTankDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnFoundAimingComponent(UTankAimingComponent* TankAimingComponent);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void AimTowardsCosshair();

public:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingCom;
};
