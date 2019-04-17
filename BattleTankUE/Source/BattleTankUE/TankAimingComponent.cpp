// MBI Copyrights

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (BerrelIsMovingOrNoAimingSolution()) {
		FiringStatus = EFiringStatus::AimingNotReady;
	}
	else {
		FiringStatus = EFiringStatus::Ready;
	}
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector AimPoint) {
	if (!ensure(Barrel)) return;

	FVector LaunchVelocity(0);
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		AimPoint,
		ProjectileInitialSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // Must be set otherwise there is a BUG
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);

	if (bHaveAimSolution) {
		AimingDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimingDirection);
	}
	else {
		AimingDirection = FVector(0);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector NewBarrelDirection){
	if (!ensure(Barrel)) return;
	if (!ensure(Turret)) return;

	/// Calculate the difference between the actual barrel rotation and and the NewBarrelDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator NewBarrelRotator = NewBarrelDirection.Rotation();
	FRotator DeltaRotator = NewBarrelRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) return;
	if (!ensure(ProjectileBlueprint)) return;

	if (FiringStatus == EFiringStatus::Reloading) return;

	LastFireTime = GetWorld()->GetTimeSeconds();
	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
	Projectile->LaunchProjectile(ProjectileInitialSpeed);
}


bool UTankAimingComponent::BerrelIsMovingOrNoAimingSolution() {
	if (!ensure(Barrel)) return false;

	FVector BarrelForwardVector = Barrel->GetForwardVector();

	/// If no aiming solution AimingDirection = FVector(0) (see AimingDirection specifications) so BarrelForwardVector.Equals(AimingDirection) = False and we need to return True since we have no aiming solution
	/// If we have an aiming solution and the BarrelForwardVector.Equals(AimingDirection) = True we must return False since Barrel is not moving
	/// If we have an aiming solution and the BarrelForwardVector.Equals(AimingDirection) = False we must return True since Barrel is moving
	return !BarrelForwardVector.Equals(AimingDirection, 0.01);
}
