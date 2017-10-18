// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrentStaticMeshComponent.h"




void UTankTurrentStaticMeshComponent::TurnTurrent(int TurnDir)
{
	float tmpDeltaTime = GetWorld()->GetDeltaSeconds();
	float tmpDeltaYaw = tmpDeltaTime * this->TurnSpeed * TurnDir;
	this->AddRelativeRotation(
		FRotator(0, tmpDeltaYaw, 0)
	);
}
