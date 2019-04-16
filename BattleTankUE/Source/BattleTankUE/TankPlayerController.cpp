// MBI Copyrights

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) return;
	FoundTankAimingComponent(TankAimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(TankAimingComponent)) return;

	FVector HitLocation(0);
	if (GetSightRayHitLocation(HitLocation)) {
		TankAimingComponent->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const{
	/// Find the crosshair position in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	/// De-project the screen crosshair position to a World Location
	FVector CrosshairLocation, CrosshairDirection;
	DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CrosshairLocation, CrosshairDirection);

	/// Ray-cast in Crosshair direction
	return GetLookVectorHitLocation(OutHitLocation, CrosshairDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector &OutHitLocation, FVector LookDirection) const {
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector RayEndPoint = CameraLocation + LookDirection * LineTraceRange;

	/// Helper Debug Line
	/*DrawDebugLine(
		GetWorld(),
		CameraLocation,
		RayEndPoint,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/

	/// Line trace along the crosshair
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		CameraLocation,
		RayEndPoint,
		ECollisionChannel::ECC_Visibility
	);
	
	if (!Hit.GetComponent()) return false;

	OutHitLocation = Hit.Location;
	return true;
}
