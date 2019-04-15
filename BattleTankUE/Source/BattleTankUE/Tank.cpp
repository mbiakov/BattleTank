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

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}


// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::AimAt(FVector AimPoint) const {
	TankAimingComponent->AimAt(AimPoint, ProjectileInitialSpeed);
}


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet) {
	TankBarrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}


void ATank::SetTurretReference(UTankTurret * TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::Fire(){
	if (!TankBarrel) {
		UE_LOG(LogTemp, Error, TEXT("UTank::Fire(): TankBarrel not found"));
		return;
	}
	if (!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("UTank::Fire(): ProjectileBlueprint not set. Please set Projectile Blueprint in the TankBP Details panel."));
		return;
	}

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTime;
	if (!isReloaded) return;

	LastFireTime = GetWorld()->GetTimeSeconds();

	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, TankBarrel->GetSocketLocation(FName("Projectile")), TankBarrel->GetSocketRotation(FName("Projectile")));
	Projectile->LaunchProjectile(ProjectileInitialSpeed);
}
