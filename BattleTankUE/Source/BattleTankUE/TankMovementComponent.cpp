// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::MoveForward(float Acceleration) {
	if (!LeftTrack || !RightTrack) {
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::MoveForward(float Acceleration): LeftTrack or RightTrack not initialized"));
		return;
	}
	LeftTrack->MoveTrack(Acceleration);
	RightTrack->MoveTrack(Acceleration);
	// TODO Prevent double speed acceleration due to dual control possibility
}


void UTankMovementComponent::TurnRight(float Acceleration) {
	if (!LeftTrack || !RightTrack) {
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::TurnRight(float Acceleration): LeftTrack or RightTrack not initialized"));
		return;
	}
	LeftTrack->MoveTrack(Acceleration);
	RightTrack->MoveTrack(-Acceleration);
	// TODO Prevent double speed acceleration due to dual control possibility
}


void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("%s: RequestDirectMove %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}
