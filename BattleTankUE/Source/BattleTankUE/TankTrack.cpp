// MBI Copyrights

#include "TankTrack.h"
#include "Suspension.h"
#include "SpawnPoint.h"
#include "Engine/World.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::AccelerateTrack(float Acceleration) {
	float TrackAcceleration = FMath::Clamp<float>(Acceleration, -2, 2);
	MoveTrack(TrackAcceleration);
}


void UTankTrack::MoveTrack(float TrackAcceleration) {
	float ForceMagnitude = TrackAcceleration * BaseMovementForce;
	TArray<ASuspension*> Suspensions = GetSuspensions();
	if (!ensure(Suspensions.Num() != 0)) return;
	float ForceMagnitudePerWheel = ForceMagnitude / Suspensions.Num();

	for (ASuspension *Suspension : Suspensions) {
		Suspension->AddDrivingForce(ForceMagnitudePerWheel);
	}
}


TArray<ASuspension*> UTankTrack::GetSuspensions() const {
	TArray<ASuspension*> ResultArray;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	for (USceneComponent *Child : Children) {
		USpawnPoint *SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) continue;
		
		ASuspension *Suspension = Cast<ASuspension>(SpawnPoint->GetSpawnedActor());
		if (!ensure(Suspension)) continue;

		ResultArray.Add(Suspension);
	}

	return ResultArray;
}
