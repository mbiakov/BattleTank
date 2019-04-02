// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should it Tick ?
}


// Called when the game starts
void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector AimPoint, float LaunchSpeed) {
	if (!Barrel) return;

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
		// TODO Delete this log
		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), GetWorld()->GetTimeSeconds());

		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	} else {
		// TODO Delete this log
		// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), GetWorld()->GetTimeSeconds());
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector NewBarrelDirection){
	/// Calculate the difference between the actual barrel rotation and and the NewBarrelDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator NewBarrelRotator = NewBarrelDirection.Rotation();
	FRotator DeltaRotator = NewBarrelRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
}
