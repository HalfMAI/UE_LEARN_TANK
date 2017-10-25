// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATankPlayerController *tmpTankPC = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (tmpTankPC)
	{
		ATank* tmpPlayerTank = tmpTankPC->GetControlledTank();
		if (tmpPlayerTank)
		{
			ATank* tmpCurrentTank = Cast<ATank>(GetPawn());
			tmpCurrentTank->AimAt(tmpPlayerTank->GetActorLocation());

			//tmpCurrentTank->Fire();


			this->MoveToActor(tmpPlayerTank, this->AcceptRadius);
		}
	}
}