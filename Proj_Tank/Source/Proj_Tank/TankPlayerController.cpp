// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	auto tmpPosedTank = Cast<ATank>(GetPawn());

	if (tmpPosedTank)
	{
		tmpPosedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}

void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPawn())
	{
		this->TankAimingCom = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		if (ensure(this->TankAimingCom))
		{
			this->OnFoundAimingComponent(TankAimingCom);
		}
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
		int32 tmpViewportSizeX, tmpViewportSizeY;
		GetViewportSize(tmpViewportSizeX, tmpViewportSizeY);
		FVector2D tmpPointLoc = FVector2D(tmpViewportSizeX * this->CrossHairLocX, tmpViewportSizeY * this->CrossHairLocY);

		FHitResult tmpHitRet;
		if (this->GetHitResultAtScreenPosition(tmpPointLoc, ECC_Visibility, false, tmpHitRet))
		{

			this->TankAimingCom->AimAt(tmpHitRet.ImpactPoint, this->TankAimingCom->LaunchSpeed);
		}
	}
}