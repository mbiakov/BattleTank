// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	// TODO Delete these test lines
	/*ATank *PlayerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("Player Tank found: %s"), *PlayerTank->GetName());*/
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
