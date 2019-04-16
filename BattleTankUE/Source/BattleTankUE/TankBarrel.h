// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Elevates the Barrel according the given RelativeSpeed and the MaxDegreesPerSecond parameter
	// The RelativeSpeed is clamped between -1 and 1 by this function
	void Elevate(float &RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 45;
};
