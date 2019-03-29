// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
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

	FVector HitLocation;
	if (GetSightRayHitLocation(&HitLocation)) {
		// TODO Delete the log
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

		// TODO Tell controlled tank to aim at this point
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector *OutHitLocation) const{
	/// Find the crosshair position in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	/// De-project the screen crosshair position to a World Location
	FVector CrosshairLocation, CrosshairDirection;
	DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, CrosshairLocation, CrosshairDirection);

	/// Get the View Point Location
	FVector ViewPointLocation;
	FRotator ViewPointRotator;
	GetPlayerViewPoint(ViewPointLocation, ViewPointRotator);

	/// Calculate the Ray-Cast end point
	/// The CrosshairDirection is 1cm long vector
	/// We take 1km projection because the landscape is 1km large
	FVector RayEndPoint = ViewPointLocation + CrosshairDirection * 100000;
	
	/// Helper Debug Line
	// TODO Comment the Debug Line
	DrawDebugLine(
		GetWorld(),
		ViewPointLocation,
		RayEndPoint,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Line trace along the crosshair
	FCollisionQueryParams TracePatameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewPointLocation,
		RayEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TracePatameters
	);

	if (!Hit.GetComponent()) return false;

	// TODO Delete the log
	UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *Hit.GetComponent()->GetName());
	*OutHitLocation = Hit.ImpactPoint;
	return true;
}
