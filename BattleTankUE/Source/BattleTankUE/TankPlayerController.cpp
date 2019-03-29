// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	/*ATank *ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Controlled Tank not found"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player posses %s"), *ControlledTank->GetName());*/
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
	/// The ViewPoint is the Ray-Cast start point
	FVector ViewPoint;
	FRotator ViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPoint, ViewPointRotator);

	/// To calculate the Ray-Cast end point we need to calculate the CrosshairRotator
	/// To calculate the CrosshairRotator we need to calculate alpha (in degrees), the angle between the center of the screen and the crosshair
	/// The horizontal field of view is 90 degrees, thus
	/// alpha = atan( (0.5 - 33.3) * ScreenSizeY / ScreenSizeX ) * 180 / Pi
	// TODO Make a general formula that depands on the horizental field of view in degrees that must be get as parameter from the player camera
	int32 ScreenSizeX;
	int32 ScreenSizeY;
	GetWorld()->GetFirstPlayerController()->GetViewportSize(ScreenSizeX, ScreenSizeY);
	// TODO Use C++ Pi
	float alpha = atan(0.334 * ScreenSizeY / ScreenSizeX) * 180 / 3.14;

	/// Crosshair Rotator has alpha degrees more in pitch than ViewPointRotator
	FRotator CrosshairRotator = ViewPointRotator.Add(alpha, 0, 0);

	/// Calculate the ray cast end point
	/// The CrosshairRotator.Vector() gives 1cm long vector
	/// We take 1km projection because the landscape is 1km large
	FVector RayEndPoint = ViewPoint + CrosshairRotator.Vector() * 100000;

	/// Helper Debug Line
	// TODO Comment the helper function
	DrawDebugLine(
		GetWorld(),
		ViewPoint,
		RayEndPoint,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Ray-cast taking into account only the landscape
	FCollisionQueryParams TracePatameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewPoint,
		RayEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TracePatameters
	);

	if (!Hit.GetComponent()) return false;

	// TODO Delete the log of the hit component name
	// UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *Hit.GetComponent()->GetName());
	*OutHitLocation = Hit.ImpactPoint;
	return true;
}
