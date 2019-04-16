// MBI Copyrights

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (!ensure(PlayerPawn && TankAimingComponent)) return;
	MoveToActor(PlayerPawn, AcceptanceRadius);
	TankAimingComponent->AimAt(PlayerPawn->GetActorLocation());
	TankAimingComponent->Fire();
}
