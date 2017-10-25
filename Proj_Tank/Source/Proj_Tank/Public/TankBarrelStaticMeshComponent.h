// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrelStaticMeshComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent)) //, hidecategories = ("Collision") )
class PROJ_TANK_API UTankBarrelStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Elevation(int ElevationDir); // 1:up, -1:down
		
	UPROPERTY(EditAnywhere, Category = Setup)
	float ElevatSpeed = 30.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 45;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0;
};
