// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Suspension.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANKUE_API ASuspension : public AActor
{
	GENERATED_BODY()
	
public:	
	ASuspension();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Mass = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Wheel = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent *Suspension = nullptr;
};
