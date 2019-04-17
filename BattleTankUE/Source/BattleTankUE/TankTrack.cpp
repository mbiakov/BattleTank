// MBI Copyrights

#include "TankTrack.h"
#include "Engine/World.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	TankMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	/// Adding OnHit event generation
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


// This function is called every frame if the Tank touches the ground. So all the movements are applied in here.
void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit) {
	MoveTrack();
	ApplySidewayFriction();
	TrackAcceleration = 0;
}


void UTankTrack::AccelerateTrack(float Acceleration) {
	TrackAcceleration = FMath::Clamp<float>(TrackAcceleration + Acceleration, -2, 2);
}


void UTankTrack::MoveTrack() {
	if (!ensure(TankMeshComponent)) return;

	FVector ForceToApply = GetForwardVector() * TrackAcceleration * BaseMovementForce;
	TankMeshComponent->AddForceAtLocation(ForceToApply, GetComponentLocation());
}


void UTankTrack::ApplySidewayFriction() {
	if (!ensure(TankMeshComponent)) return;

	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector AccelerationCorrection = - SlippageSpeed / DeltaTime * GetRightVector();
	FVector ForceToApply = TankMeshComponent->GetMass() * AccelerationCorrection / 2; /// We devide by 2 because there is 2 tracks
	TankMeshComponent->AddForce(ForceToApply);
}
