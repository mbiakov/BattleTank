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
	if (!GetControlledTank()) return;

	FVector HitLocation;
	GetSightRayHitLocation(&HitLocation);
	// UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

	// Get the world location of linetrace through crosshair
	// If it hit landscape
		// Tell controlled tank to aim at this point
}


bool ATankPlayerController::GetSightRayHitLocation(FVector *OutHitLocation) const{
	FVector ViewPoint;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPoint, ViewPointRotation);

	// TODO Calculate the crosshair point Rotator
	// TODO Get and verify the Viewport Size
	int32 ScreenSizeX;
	int32 ScreenSizeY;
	GetWorld()->GetFirstPlayerController()->GetViewportSize(ScreenSizeX, ScreenSizeY);
	// UE_LOG(LogTemp, Warning, TEXT("X: %s, Y: %s"), *FString::FromInt(ScreenSizeX), *FString::FromInt(ScreenSizeY));
	FRotator CrosshairPointRotation = ViewPointRotation;

	// Calculate the final reachable point (we take at maximum a kilometer projection because the landscape is 1 km)
	FVector FinalReachablePoint = ViewPoint + CrosshairPointRotation.Vector() * 100 * 1000; // in cm *100 gives 1m and * 1000 gives 1km

	// TODO Delete this Helper function
	// Helper Debug Line
	DrawDebugLine(
		GetWorld(),
		ViewPoint,
		FinalReachablePoint,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	// Ray-cast taking into account only landscape
	FCollisionQueryParams TracePatameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewPoint,
		FinalReachablePoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TracePatameters
	);

	if (!Hit.GetComponent()) return false;

	// UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *Hit.GetComponent()->GetName());
	*OutHitLocation = Hit.ImpactPoint;
	return true;
}
