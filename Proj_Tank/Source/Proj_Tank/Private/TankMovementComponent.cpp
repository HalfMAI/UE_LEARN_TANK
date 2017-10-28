// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::InitTankMovementComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Dir)
{
	if (!ensure(this->LeftTrack && this->RightTrack))
	{
		return;
	}

	this->LeftTrack->SetThrottle(Dir);
	this->RightTrack->SetThrottle(Dir);
}

void UTankMovementComponent::IntendTrunRight(float Dir)
{
	if (!ensure(this->LeftTrack && this->RightTrack))
	{
		return;
	}

	
	this->LeftTrack->SetThrottle(Dir);
	this->RightTrack->SetThrottle(-Dir);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector tmpForwardDir = this->GetOwner()->GetActorForwardVector();
	FVector tmpDesDir = MoveVelocity.GetSafeNormal();

	float tmpDotProduct = FVector::DotProduct(tmpForwardDir, tmpDesDir);
	FVector tmpCrossProduct = FVector::CrossProduct(tmpForwardDir, tmpDesDir);
	this->IntendMoveForward(tmpDotProduct);
	this->IntendTrunRight(tmpCrossProduct.Z);
}
