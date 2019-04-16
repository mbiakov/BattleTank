// MBI Copyrights

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float &RelativeSpeed) {
	/// Relative speed must be clamped between -1 and 1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float RotationChangeByFrame = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChangeByFrame;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
