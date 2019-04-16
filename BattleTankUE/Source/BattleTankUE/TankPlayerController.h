// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class UTankAimingComponent;

/*
* Attaches the PlayerUI to the Viewport and Ray-Cast trough the Crosshair. Then calls the Aiming Component with the found position.
* The conrtolled Pawn must have an UTankAimingComponent.
**/
UCLASS()
class BATTLETANKUE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundTankAimingComponent(UTankAimingComponent *TankAimingComponent);

private:
	UTankAimingComponent *TankAimingComponent = nullptr;

	// Start the Tank moving the Barrel so that a shot will hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	// Returns true if hit landscape and modify the OUT parameter with world location of ray-cast through crosshair
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	float CrosshairXLocation = 0.5;
	float CrosshairYLocation = 0.33333;

	float LineTraceRange = 100000;

	// Ray-cast in LookDirection from the ViewPoint
	// LookDirection must be 1cm long vector
	// Returns true if something is hit and sets OutHitLocation
	bool GetLookVectorHitLocation(FVector &OutHitLocation, FVector LookDirection) const;
};
