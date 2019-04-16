// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
* Responsible for the Tank movements
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Acceleration);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TurnRight(float Acceleration);

private:
	// This method is used by the Unreal pathfinding mechanism.
	// It is called with MoveVelocity vector that indicates where the object must move to reach the Actor given in the AAIController::MoveToActor() method.
	// We override this method with our Tank Movement System.
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};
