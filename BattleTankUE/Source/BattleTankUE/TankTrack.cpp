// MBI Copyrights

#include "TankTrack.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	TankMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplySidewayFriction(DeltaTime);
}


void UTankTrack::MoveTrack(float Acceleration) {
	if (!ensure(TankMeshComponent)) return;

	FVector ForceToApply = GetForwardVector() * Acceleration * BaseMovementForce;
	TankMeshComponent->AddForceAtLocation(ForceToApply, GetComponentLocation());
}


void UTankTrack::ApplySidewayFriction(float DeltaTime) {
	if (!ensure(TankMeshComponent)) return;

	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	FVector AccelerationCorrection = - SlippageSpeed / DeltaTime * GetRightVector();
	FVector ForceToApply = TankMeshComponent->GetMass() * AccelerationCorrection / 2; /// We devide by 2 because there is 2 tracks
	TankMeshComponent->AddForce(ForceToApply);
}