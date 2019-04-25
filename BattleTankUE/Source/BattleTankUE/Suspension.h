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
	void AddDrivingForce(float ForceMagnitude);

private:
	void ApplyForce();
	float ForceMagnitudeToApplyThisFrame = 0;

	void SetupConstrainedComponents();

	// Components
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent *Suspension = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Axis = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent *WheelRotationConstraint = nullptr;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Wheel = nullptr;

	ASuspension();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
