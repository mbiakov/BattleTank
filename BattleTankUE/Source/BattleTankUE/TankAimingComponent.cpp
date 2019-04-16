// MBI Copyrights

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector AimPoint, float LaunchSpeed) {
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::AimAt(FVector AimPoint, float LaunchSpeed): Barrel not found"));
		return;
	}

	FVector LaunchVelocity(0);
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		AimPoint,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // Must be set otherwise there is a BUG
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);

	if (bHaveAimSolution) {
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector NewBarrelDirection){
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::MoveBarrelTowards(FVector NewBarrelDirection): Barrel not found"));
		return;
	}
	if (!Turret) {
		UE_LOG(LogTemp, Error, TEXT("UTankAimingComponent::MoveBarrelTowards(FVector NewBarrelDirection): Turret not found"));
		return;
	}

	/// Calculate the difference between the actual barrel rotation and and the NewBarrelDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator NewBarrelRotator = NewBarrelDirection.Rotation();
	FRotator DeltaRotator = NewBarrelRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
