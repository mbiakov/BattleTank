// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

UCLASS()
class BATTLETANKUE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank *AIControlledTank = nullptr;
	ATank *PlayerTank = nullptr;

	// How close the AI Tank can get to the player
	float AcceptanceRadius = 1000;
};
