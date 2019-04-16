// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;
class UTankAimingComponent;

/*
* Finds out the Player Pawn then moves to the player location and aims the player thanks to the UTankAimingComponent of the controlled Pawn.
* The controlled Pawn must have an UTankAimingComponent.
**/
UCLASS()
class BATTLETANKUE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank *AIControlledTank = nullptr;
	UTankAimingComponent *TankAimingComponent = nullptr;
	APawn *PlayerPawn = nullptr;

	// How close the AI Tank can get to the player
	float AcceptanceRadius = 1000;
};
