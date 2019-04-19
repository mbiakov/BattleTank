// MBI Copyrights

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	if (!InPawn) return; // The method is called at the end of the game with a nullptr InPawn

	TankAimingComponent = InPawn->FindComponentByClass<UTankAimingComponent>();
	ATank *AITank = Cast<ATank>(InPawn);
	if (!ensure(AITank)) return;
	AITank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
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


void ATankAIController::OnPossessedTankDeath() {
	GetPawn()->DetachFromControllerPendingDestroy();
}
