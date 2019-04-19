// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKUE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth = StartingHealth;
};
