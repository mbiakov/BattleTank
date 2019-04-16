// MBI Copyrights

#include "TankTrack.h"


void UTankTrack::MoveTrack(float Acceleration) {
	FVector ForceToApply = GetForwardVector() * Acceleration * BaseMovementForce;
	UPrimitiveComponent *TankPrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankPrimitiveComponent)) return;
	TankPrimitiveComponent->AddForceAtLocation(ForceToApply, GetComponentLocation());
}
