// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurrentStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJ_TANK_API UTankTurrentStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void TurnTurrent(int TurnDir); // 1:right, -1:left


	UPROPERTY(EditAnywhere, Category = Setup)
	float TurnSpeed = 30.0f;
};
