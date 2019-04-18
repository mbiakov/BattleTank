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

	if (!ensure(PlayerPawn)) return;
	if (!ensure(TankAimingComponent)) return;

	MoveToActor(PlayerPawn, AcceptanceRadius);

	TankAimingComponent->AimAt(PlayerPawn->GetActorLocation());

	if (TankAimingComponent->GetFiringStatus() == EFiringStatus::Ready) {
		TankAimingComponent->Fire();
	}
}
