// MBI Copyrights

#include "Tank.h"


ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	float DamageAmountToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);

	CurrentHealth = CurrentHealth - DamageAmountToApply;

	UE_LOG(LogTemp, Warning, TEXT("Remaining Health: %f"), CurrentHealth);

	if (CurrentHealth <= 0) {
		// TODO Trigger the die event
		UE_LOG(LogTemp, Warning, TEXT("Must Die"));
	}

	return DamageAmountToApply;
}
