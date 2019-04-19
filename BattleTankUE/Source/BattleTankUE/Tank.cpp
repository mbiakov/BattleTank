// MBI Copyrights

#include "Tank.h"


ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	float DamageAmountToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);

	CurrentHealth = CurrentHealth - DamageAmountToApply;

	if (CurrentHealth <= 0) {
		OnTankDeath.Broadcast();
	}

	return DamageAmountToApply;
}


float ATank::GetHealthPercentage() const {
	if (!ensure(StartingHealth != 0)) return 0;
	return CurrentHealth / StartingHealth;
}
