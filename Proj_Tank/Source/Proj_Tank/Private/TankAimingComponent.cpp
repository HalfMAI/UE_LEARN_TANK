// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	//TODO add Tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed)
{
	if (!this->IsComponentSetupOK())	{ return; }


	FVector tmpStartLoc = this->Barrel->GetSocketLocation(FName("LaunchPoint"));
	FVector tmpEndLoc = HitLocation;

	FVector resultVelocity;
	bool isGotResult = UGameplayStatics::SuggestProjectileVelocity(
		this,
		resultVelocity,
		tmpStartLoc,
		tmpEndLoc,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::OnlyTraceWhileAscending,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>({ this->GetOwner() }),
		false
	);


	FString tmpTankName = GetOwner()->GetName();
	FVector tmpBarrelLocation = this->Barrel->GetComponentLocation();
	if (isGotResult)
	{
		resultVelocity = resultVelocity.GetSafeNormal();
		this->MoveBarrelTowards(resultVelocity);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrelStaticMeshComponent * Ballel)
{
	this->Barrel = Ballel;
}

void UTankAimingComponent::SetTurrentReference(UTankTurrentStaticMeshComponent * Turrent)
{
	this->Turrent = Turrent;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!this->IsComponentSetupOK())
	{
		return;
	}

	FRotator tmpCurBarrelRotator = this->Barrel->GetForwardVector().Rotation();
	FRotator tmpTurrentRotator = this->Turrent->GetForwardVector().Rotation();

	int tmpPitchDir = (AimDirection.Rotation().Pitch > tmpCurBarrelRotator.Pitch) ? 1 : -1;
	int tmpYawDir = (AimDirection.Rotation().Yaw > tmpTurrentRotator.Yaw) ? 1 : -1;

	this->Barrel->Elevation(tmpPitchDir);
	this->Turrent->TurnTurrent(tmpYawDir);
}

bool UTankAimingComponent::IsComponentSetupOK() const
{
	return 
		this->Barrel && this->Turrent
		;
}

