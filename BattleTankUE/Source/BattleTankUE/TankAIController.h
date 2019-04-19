// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class UTankAimingComponent;

/**
* Finds out the Player Pawn then moves to the player location and aims the player thanks to the UTankAimingComponent of the controlled Pawn.
* The AI controlled Pawn must have an UTankAimingComponent.
*/
UCLASS()
class BATTLETANKUE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

protected:
	// How close the AI Tank can get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 8000;

private:
	UFUNCTION()
	void OnPossessedTankDeath();

	UTankAimingComponent *TankAimingComponent = nullptr;
	APawn *PlayerPawn = nullptr;
};
