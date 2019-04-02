// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	// TODO Delete these test lines
	/*ATank *PlayerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("Player Tank found: %s"), *PlayerTank->GetName());*/
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	ATank *PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		// TODO Move towards the player

		/// Aime towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire if ready
	}
}


ATank * ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const {
	APawn *PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("Player Pawn not found"));
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
