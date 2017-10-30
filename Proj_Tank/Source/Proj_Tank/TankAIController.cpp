// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	this->TankAimingCom = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ensure(this->TankAimingCom);

	uint8 tmpN = FMath::RandRange(0, static_cast<int>(EAITankMoveType::EEND) - 1);
	this->CurrentMoveType = static_cast<EAITankMoveType>(tmpN);
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

			if (this->TankAimingCom->GetFinringStatus() == EFiringStatus::Locked && this->IsCanFire)
			{
				this->TankAimingCom->Fire();
			}
		}

		FVector tmpTankLoc = tmpPlayerTank->GetNavAgentLocation();
		switch (this->CurrentMoveType)
		{
		case EAITankMoveType::Follow :
			this->MoveToActor(tmpPlayerTank, this->AcceptRadius);
			break;
		case EAITankMoveType::Block :
			this->MoveToLocation(tmpTankLoc + tmpPlayerTank->GetActorForwardVector() * this->MoveTypeDistance, this->AcceptRadius);
			break;
		case EAITankMoveType::Right:
			this->MoveToLocation(tmpTankLoc + tmpPlayerTank->GetActorRightVector() * this->MoveTypeDistance, this->AcceptRadius);
			break;
		case EAITankMoveType::Left:
			this->MoveToLocation(tmpTankLoc + tmpPlayerTank->GetActorRightVector() * -this->MoveTypeDistance, this->AcceptRadius);
			break;
		default:
			break;
		}
	}
}