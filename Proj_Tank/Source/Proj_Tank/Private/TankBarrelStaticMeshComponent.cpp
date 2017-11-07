// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelStaticMeshComponent.h"

void UTankBarrelStaticMeshComponent::Elevation(int ElevationDir)
{
	float tmpDeltaTime = GetWorld()->GetDeltaSeconds();
	float tmpCurPitch = this->RelativeRotation.Pitch + tmpDeltaTime * this->ElevatSpeed * ElevationDir;
	tmpCurPitch = FMath::Clamp<float>(tmpCurPitch, this->MinElevationDegree, this->MaxElevationDegree);
	this->SetRelativeRotation(
		FRotator(tmpCurPitch, 0, 0)
	);
}

