// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->TankAimingCom = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(this->TankAimingCom))
	{
		this->OnFoundAimingComponent(TankAimingCom);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AimTowardsCosshair();
}

void ATankPlayerController::AimTowardsCosshair()
{
	if (GetPawn())
	{
		/*int32 tmpViewportSizeX, tmpViewportSizeY;
		GetViewportSize(tmpViewportSizeX, tmpViewportSizeY);
		FVector2D tmpPointLoc = FVector2D(tmpViewportSizeX * this->CrossHairLocX, tmpViewportSizeX * this->CrossHairLocY);

		FHitResult tmpHitRet;
		if (this->GetHitResultAtScreenPosition(tmpPointLoc, ECC_Visibility, false, tmpHitRet))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitName: %s, Hit Location: %s"), *(tmpHitRet.GetActor()->GetName()), *(tmpHitRet.ImpactPoint.ToString()));
		}*/

		FVector tmpHitLocation;		
		if (this->GetSightRayHitLoaction(tmpHitLocation))
		{
			this->TankAimingCom->AimAt(tmpHitLocation, this->TankAimingCom->LaunchSpeed); //TODO get launch speed
		}
	}
}

bool ATankPlayerController::GetSightRayHitLoaction(OUT FVector& out_HitLocation) const
{		
	FVector tmpCamWorldLocation, tmpCamWorldDirection;
	if (this->GetCossHairLookLocationAndDirection(OUT tmpCamWorldLocation, OUT tmpCamWorldDirection))
	{
		FVector tmpLoc;

		return GetLookVectorHitLocation(tmpCamWorldLocation, tmpCamWorldDirection, out_HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookLocation, FVector& LookDirection, OUT FVector& out_HitLocation) const
{

	FVector tmpStart, tmpEnd;
	tmpStart = LookLocation;
	tmpEnd = tmpStart + LookDirection * LineTraceRange;

	FHitResult tmpHitResult;
	GetWorld()->LineTraceSingleByChannel(OUT tmpHitResult, tmpStart, tmpEnd, ECollisionChannel::ECC_Visibility);

	out_HitLocation = tmpHitResult.ImpactPoint;

	if (tmpHitResult.GetActor()){ return true; } else { return false; }
}

bool ATankPlayerController::GetCossHairLookLocationAndDirection(OUT FVector& OutCamWorldLocation, OUT FVector& OutCamWorldDirection) const
{
	int32 tmpViewportSizeX, tmpViewportSizeY;
	GetViewportSize(tmpViewportSizeX, tmpViewportSizeY);
	FVector2D ScreenLoc = FVector2D(tmpViewportSizeX * this->CrossHairLocX, tmpViewportSizeY * this->CrossHairLocY);
	return this->DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, OutCamWorldLocation, OutCamWorldDirection);
}

