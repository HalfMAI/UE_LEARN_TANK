// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankProjectile.h"
#include "Tank.generated.h"

UCLASS()
class PROJ_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation) const;

protected:
	UTankAimingComponent* TankAimingCom;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementCom;

private:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelStaticMeshComponent* Ballel);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurrentRefrence(UTankTurrentStaticMeshComponent* Turrent);

	UFUNCTION(BlueprintCallable, Category = Battle)
	void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<ATankProjectile> TankProjectileBlueprint;

protected:
	UTankBarrelStaticMeshComponent* BallelMeshRef;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

private:
	double ReloadLastUpdateTime = 0.0f;
};
