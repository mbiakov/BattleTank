// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enum defining Aiming State
UENUM()
enum class EFiringStatus : uint8 {
	NoRemainingAmmunitions,
	Ready,
	AimingNotReady,
	Reloading
};

/**
* Requirements:
*   - This component must be initialized with a Turret and a Barrel at BeginPlay.
*   - The Barrel mesh must have a Projectile Socket.
*   - A Projectile Blueprint must be set in the Details.
* Responsible for the Tank aiming, firing and Barrel/Turret movements.
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector AimPoint);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int GetRemainingAmmunitions() const;


protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);


private:
	void MoveBarrelTowards(FVector NewBarrelDirection);

	bool BerrelIsMovingOrNoAimingSolution();

	void UpdateFiringStatus();

	UTankBarrel *Barrel = nullptr;

	UTankTurret *Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileInitialSpeed = 3500;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Used in BerrelIsMovingOrNoAimingSolution to compare to the actual Barrel direction. Updated each time the aiming method is called. If there is no aiming solution, the vector is set to FVector(0).
	FVector AimingDirection = FVector(0);

	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	int RemainingAmmunitions = 3;
};
