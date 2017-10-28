// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"

#include "TankTrack.h"



#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PROJ_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitTankMovementComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack);


	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Dir);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTrunRight(float Dir);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	
};
