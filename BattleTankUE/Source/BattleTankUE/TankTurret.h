// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Rotates the Turret according the given RelativeSpeed and the MaxDegreesPerSecond parameter
	// The RelativeSpeed is clamped between -1 and 1 by this function
	void Rotate(float &RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 50;
};
