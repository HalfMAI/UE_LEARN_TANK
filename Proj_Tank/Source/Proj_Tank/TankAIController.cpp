// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController ControlledTank: %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Do not have Controlled Tank!"));
	}

	auto tmpPlayerControlledTank = this->GetPlayerTank();
	if (tmpPlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Get Player ControlledTank: %s"), *(tmpPlayerControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Get Player ControlledTank Do not have Controlled Tank!"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* tmpPlayerTank = this->GetPlayerTank();
	if (tmpPlayerTank)
	{
		this->GetControlledTank()->AimAt(tmpPlayerTank->GetActorLocation());
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* tmpPC = GetWorld()->GetFirstPlayerController();
	ATankPlayerController* tmpTankPC = Cast<ATankPlayerController>(tmpPC);
	if (tmpTankPC)
	{
		return tmpTankPC->GetControlledTank();
	}
	return nullptr;
}
