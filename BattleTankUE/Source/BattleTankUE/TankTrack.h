// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// Maximum Force in Newtons that is applied by the Track to make the Tank move
	// To set 1g acceleration on a 40 tonnes Tank we need about 400 000 Newtons
	// Unreal base distance unit is centimeters
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float BaseMovementForce = 37500000;
};
