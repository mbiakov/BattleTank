// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;

// Enum defining Aiming State
UENUM()
enum class EFiringStatus : uint8 {
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKUE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel *BarrelToSet);

	void SetTurretReference(UTankTurret *TurretToSet);

	void AimAt(FVector AimPoint, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel *Barrel = nullptr;

	UTankTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector NewBarrelDirection);
};
