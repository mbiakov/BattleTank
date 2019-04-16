// MBI Copyrights

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

	if (!ensure(PlayerTank && AIControlledTank)) return;
	MoveToActor(PlayerTank, AcceptanceRadius);
	AIControlledTank->AimAt(PlayerTank->GetActorLocation());
	AIControlledTank->Fire();
}
