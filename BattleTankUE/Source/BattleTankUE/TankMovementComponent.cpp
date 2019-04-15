// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) {
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent: Initialize called without LeftTrack or RightTrack pointer"));
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::MoveForward(float Acceleration) {
	LeftTrack->MoveTrack(Acceleration);
	RightTrack->MoveTrack(Acceleration);
	// TODO Prevent double speed acceleration due to dual control possibility
}
