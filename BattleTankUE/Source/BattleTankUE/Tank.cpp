// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::AimAt(FVector AimPoint) const {
	FindComponentByClass<UTankAimingComponent>()->AimAt(AimPoint, ProjectileInitialSpeed);
}


void ATank::Fire(){
	/// Verify if the Tank is ready to fire regarding reload time and set LastFireTime if so
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTime;
	if (!isReloaded) return;
	LastFireTime = GetWorld()->GetTimeSeconds();

	UTankBarrel *TankBarrel = FindComponentByClass<UTankBarrel>();
	if (!TankBarrel) {
		UE_LOG(LogTemp, Error, TEXT("UTank::Fire(): TankBarrel not found"));
		return;
	}
	if (!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("UTank::Fire(): ProjectileBlueprint not set. Please set Projectile Blueprint in the TankBP Details panel."));
		return;
	}

	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, TankBarrel->GetSocketLocation(FName("Projectile")), TankBarrel->GetSocketRotation(FName("Projectile")));
	Projectile->LaunchProjectile(ProjectileInitialSpeed);
}
