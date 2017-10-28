// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	this->TankAimingCom = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ensure(this->TankAimingCom);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATankPlayerController *tmpTankPC = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	auto tmpPlayerTank = tmpTankPC->GetPawn();
	if (tmpTankPC && tmpPlayerTank)
	{
		if (this->TankAimingCom)
		{
			FVector tmpLoc = tmpPlayerTank->GetActorLocation();
			this->TankAimingCom->AimAt(tmpLoc, this->TankAimingCom->LaunchSpeed);
			this->TankAimingCom->Fire();
		}


		this->MoveToActor(tmpPlayerTank, this->AcceptRadius);
	}
}