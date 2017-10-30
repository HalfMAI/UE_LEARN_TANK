// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GameFramework/Actor.h"
#include "TankBarrelStaticMeshComponent.h"
#include "TankTurrentStaticMeshComponent.h"
#include "TankProjectile.h"


#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"



UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	NoAmmo,
	EEND
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJ_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitTankAimingComponent(UTankBarrelStaticMeshComponent * Ballel, UTankTurrentStaticMeshComponent * Turrent);

	void AimAt(FVector& HitLocation, float LaunchSpeed);
	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrelStaticMeshComponent* GetBarrelReference() const;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	EFiringStatus GetFinringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	int GetAmmoNum() const;

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void Fire();
private:
	UTankBarrelStaticMeshComponent *Barrel = nullptr;
	UTankTurrentStaticMeshComponent *Turrent = nullptr;

	bool IsComponentSetupOK() const;

	bool IsBallelMoving() const;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EFiringStatus CurFiringStatus = EFiringStatus::Reloading;
	


public:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ATankProjectile> TankProjectileBlueprint;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0f;

	UPROPERTY(EditAnywhere)
	int CurrentAmmoNum = 3;

private:
	double ReloadLastUpdateTime = 0.0f;

	FVector AimingDirection = FVector::ZeroVector;
};
