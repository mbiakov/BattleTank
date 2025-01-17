// MBI Copyrights

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
}


void ATankPlayerController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	if (!InPawn) return; // The method is called at the end of the game with a nullptr InPawn

	TankAimingComponent = InPawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) return;
	FoundTankAimingComponent(TankAimingComponent);

	ATank *PlayerTank = Cast<ATank>(InPawn);
	if (!ensure(PlayerTank)) return;
	PlayerTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
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
		ECollisionChannel::ECC_Camera
	);
	
	if (!Hit.GetComponent()) return false;

	OutHitLocation = Hit.Location;
	return true;
}


void ATankPlayerController::OnPossessedTankDeath() {
	StartSpectatingOnly();
}
