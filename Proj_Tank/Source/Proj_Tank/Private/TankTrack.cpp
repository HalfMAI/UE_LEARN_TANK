// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::ApplySidewayForce()
{
	auto tmpSlippageSpeed = FVector::DotProduct(this->GetRightVector(), this->GetComponentVelocity());
	auto tmpAcce = -(tmpSlippageSpeed / GetWorld()->GetTimeSeconds()) * this->GetRightVector();

	auto tmpRootComponent = Cast<UPrimitiveComponent>(GetAttachmentRoot());
	auto tmpForce = tmpRootComponent->GetMass() * tmpAcce / 2; // F = ma. Two track-> /2;

	tmpRootComponent->AddForce(tmpForce * 0.7f);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// Two Input node (Foward and Right), so the Throttle need to add CurrentThrottle;
	this->CurrentThrottle = FMath::Clamp(this->CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveThrottle(float Throttle)
{
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(GetForwardVector() * this->TrackMaxDrivingForce * Throttle, GetComponentLocation());
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	this->ApplySidewayForce();
	this->DriveThrottle(this->CurrentThrottle);

	this->CurrentThrottle = 0;
}

