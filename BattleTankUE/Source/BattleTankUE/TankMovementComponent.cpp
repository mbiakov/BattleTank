// MBI Copyrights

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::MoveForward(float Acceleration) {
	if (!ensure(LeftTrack)) return;
	if (!ensure(RightTrack)) return;
	LeftTrack->AccelerateTrack(Acceleration);
	RightTrack->AccelerateTrack(Acceleration);
}


void UTankMovementComponent::TurnRight(float Acceleration) {
	if (!ensure(LeftTrack)) return;
	if (!ensure(RightTrack)) return;
	LeftTrack->AccelerateTrack(Acceleration);
	RightTrack->AccelerateTrack(-Acceleration);
}


void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	FVector AIMovementIntention = MoveVelocity.GetSafeNormal();
	FVector AITankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float AIIntendedForwardAcceleration = FVector::DotProduct(AITankDirection, AIMovementIntention);
	MoveForward(AIIntendedForwardAcceleration);

	float AIIntendedRightAcceleration = FVector::CrossProduct(AITankDirection, AIMovementIntention).Z;
	TurnRight(AIIntendedRightAcceleration);
}
