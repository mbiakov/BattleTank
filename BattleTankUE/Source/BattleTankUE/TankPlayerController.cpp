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
		// TODO Delete the hit location log
		// UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

		// TODO Tell controlled tank to aim at this point
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector *OutHitLocation) const{
	/// Find the crosshair position in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// TODO De-project the screen crosshair position to a World Location

	// TOD Line trace along crosshair and see what we hit in a specific rang

	return true;

	/// ------------------- Helper Functinos ----------------------

	/// Helper Debug Line
	/*DrawDebugLine(
		GetWorld(),
		ViewPoint,
		RayEndPoint,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/

	/// Ray-cast taking into account only the landscape
	/*FCollisionQueryParams TracePatameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewPoint,
		RayEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TracePatameters
	);*/

	// if (!Hit.GetComponent()) return false;

	// TODO Delete the hit component name log
	// UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *Hit.GetComponent()->GetName());
	// *OutHitLocation = Hit.ImpactPoint;
}
