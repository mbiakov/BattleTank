// MBI Copyrights

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AIControlledTank = Cast<ATank>(GetPawn());
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (!ensure(PlayerPawn && AIControlledTank && TankAimingComponent)) return;
	MoveToActor(PlayerPawn, AcceptanceRadius);
	TankAimingComponent->AimAt(PlayerPawn->GetActorLocation());
	AIControlledTank->Fire();
}
