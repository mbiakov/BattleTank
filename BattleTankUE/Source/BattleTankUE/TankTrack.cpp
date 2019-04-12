// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	// TODO Clamp the input value -1 to 1
	FVector ForceToApply = GetForwardVector() * Throttle * BaseMovementForce;
	UPrimitiveComponent *TankPrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankPrimitiveComponent->AddForceAtLocation(ForceToApply, GetComponentLocation());
	
	// TODO Delete the log
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Tank);
}
