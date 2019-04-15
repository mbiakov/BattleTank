// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::MoveTrack(float Acceleration) {
	// TODO Clamp the input value -1 to 1
	FVector ForceToApply = GetForwardVector() * Acceleration * BaseMovementForce;
	UPrimitiveComponent *TankPrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankPrimitiveComponent->AddForceAtLocation(ForceToApply, GetComponentLocation());
}
