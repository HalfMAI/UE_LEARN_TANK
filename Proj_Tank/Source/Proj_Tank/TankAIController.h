// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

#include "TankAIController.generated.h"


UENUM()
enum class EAITankMoveType : uint8
{
	Follow,
	Block,
	Right,
	Left,
	EEND
};


/**
 * 
 */
UCLASS()
class PROJ_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
	void OnPossedTankDeath();

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptRadius = 5000;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MoveTypeDistance = 8000;

	UPROPERTY(EditAnywhere, Category = "Setup")
	bool IsCanFire = true;

	UPROPERTY(EditAnywhere, Category = "MoveType")
	EAITankMoveType CurrentMoveType = EAITankMoveType::Follow;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingCom;
};
