// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Error, TEXT("Player Controlled Tank not found"));
		return;
	}

	FVector HitLocation(0);
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
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
