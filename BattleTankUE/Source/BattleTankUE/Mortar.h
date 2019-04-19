// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);

UCLASS()
class BATTLETANKUE_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	FMortarDelegate OnMortarDeath;

private:
	AMortar();
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;
};
