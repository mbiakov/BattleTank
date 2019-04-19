// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKUE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	FTankDelegate OnTankDeath;

private:
	ATank();
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;
};
