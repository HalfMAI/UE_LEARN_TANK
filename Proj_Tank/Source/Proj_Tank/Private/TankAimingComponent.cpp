// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	this->ReloadLastUpdateTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool tmpIsReloaded = (FPlatformTime::Seconds() - this->ReloadLastUpdateTime > this->ReloadTime);
	if (this->IsBallelMoving())
	{
		this->CurFiringStatus = EFiringStatus::Aiming;
	}
	else if (!tmpIsReloaded)
	{
		this->CurFiringStatus = EFiringStatus::Reloading;
	}
	else 
	{
		this->CurFiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::InitTankAimingComponent(UTankBarrelStaticMeshComponent * Ballel, UTankTurrentStaticMeshComponent * Turrent)
{
	ensure(Ballel && Turrent);
	this->Barrel = Ballel;
	this->Turrent = Turrent;
}

void UTankAimingComponent::Fire()
{
	bool tmpIsReloaded = (FPlatformTime::Seconds() - this->ReloadLastUpdateTime > this->ReloadTime);

	if (tmpIsReloaded)
	{
		FName tmpSocketName = FName("ProjectileSpawnLocation");
		FVector tmpLoc = this->Barrel->GetSocketLocation(tmpSocketName);
		FRotator tmpRot = this->Barrel->GetSocketRotation(tmpSocketName);

		ATankProjectile* tmpProjectile = GetWorld()->SpawnActor<ATankProjectile>(this->TankProjectileBlueprint, tmpLoc, tmpRot);
		tmpProjectile->LaunchProjectile(this->LaunchSpeed);

		this->ReloadLastUpdateTime = FPlatformTime::Seconds();
	}
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

		this->AimingDirection = resultVelocity;

		this->MoveBarrelTowards(resultVelocity);
	}
}

UTankBarrelStaticMeshComponent* UTankAimingComponent::GetBarrelReference() const
{
	return this->Barrel;
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

	UE_LOG(LogTemp, Warning, TEXT("bbb: %s"), *AimDirection.Rotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("aaa: %s"), *tmpTurrentRotator.ToString());

	this->Barrel->Elevation(tmpPitchDir);
	this->Turrent->TurnTurrent(tmpYawDir);
}

bool UTankAimingComponent::IsComponentSetupOK() const
{
	return 
		this->Barrel && this->Turrent
		;
}

bool UTankAimingComponent::IsBallelMoving() const
{
	if (!ensure(this->Barrel))
	{
		return false;
	}

	FVector tmpCurBarrelDirection = this->Barrel->GetForwardVector();
	if (this->AimingDirection.Equals(tmpCurBarrelDirection, 0.1f))
	{
		return false;
	}
	return true;
}