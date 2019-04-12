// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AIControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (PlayerTank) {
		// TODO Move towards the player

		/// Aime towards the player
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());

		AIControlledTank->Fire(); // TODO Don't Fire every frame
	}
}
