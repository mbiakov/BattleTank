// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	// TODO Delete the log
	UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *GetName(), Throttle);

	// TODO Clamp the input value -1 to 1
}
