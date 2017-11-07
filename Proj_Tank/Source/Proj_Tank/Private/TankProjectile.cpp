// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"


// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->CollisionMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(this->CollisionMeshComponent);
	this->CollisionMeshComponent->SetNotifyRigidBodyCollision(true);
	this->CollisionMeshComponent->SetVisibility(false);

	this->LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlastParticleSystemComponent"));
	this->LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	this->ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlastParticleSystemComponent"));
	this->ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->ImpactBlast->bAutoActivate = false;

	this->TankProjectileMC = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMoventComponent"));	
	this->TankProjectileMC->bAutoActivate = false;

	this->ExplosionRadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Froce Component"));
	this->ExplosionRadialForceComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	this->CollisionMeshComponent->OnComponentHit.AddDynamic(this, &ATankProjectile::OnHit);
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankProjectile::LaunchProjectile(float LaunchSpeed) const
{
	this->TankProjectileMC->SetVelocityInLocalSpace(LaunchSpeed * FVector::ForwardVector);
	this->TankProjectileMC->Activate();
}

UStaticMeshComponent * ATankProjectile::GetCollisionCom() const
{
	return this->CollisionMeshComponent;
}

void ATankProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (this->Instigator == (APawn*)OtherActor)
	{
		return;
	}

	if (this->LaunchBlast)
	{
		this->LaunchBlast->Deactivate();
	}
	if (this->ImpactBlast)
	{
		this->ImpactBlast->Activate();
		SetRootComponent(this->ImpactBlast);
	}
	if (this->CollisionMeshComponent)
	{
		this->CollisionMeshComponent->DestroyComponent();
	}
	if (this->ExplosionRadialForceComponent)
	{
		this->ExplosionRadialForceComponent->FireImpulse();
	}

	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionRadialForceComponent->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	FTimerHandle tmpTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(tmpTimerHandle,this, &ATankProjectile::OnDestoryTimerCalled, this->DestroyDelay, false);
}

void ATankProjectile::OnDestoryTimerCalled()
{
	this->Destroy();
}