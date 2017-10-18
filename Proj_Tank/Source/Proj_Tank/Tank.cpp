// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->TankAimingCom = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	this->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

//// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrelStaticMeshComponent * Ballel)
{
	this->TankAimingCom->SetBarrelReference(Ballel);
}

void ATank::SetTurrentRefrence(UTankTurrentStaticMeshComponent * Turrent)
{
	this->TankAimingCom->SetTurrentReference(Turrent);
}

void ATank::Fire() const
{
	UE_LOG(LogTemp, Warning, TEXT("Fire~"));
}

void ATank::AimAt(FVector HitLocation) const
{
	this->TankAimingCom->AimAt(HitLocation, this->LaunchSpeed);
}