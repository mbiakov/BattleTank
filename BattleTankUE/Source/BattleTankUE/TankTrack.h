// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AccelerateTrack(float Acceleration);

private:
	UTankTrack();
	virtual void BeginPlay() override;

	void ApplySidewayFriction();

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	void MoveTrack();

	UStaticMeshComponent *TankMeshComponent = nullptr;
	float TrackAcceleration = 0;

	// Maximum Force in Newtons that is applied by the Track to make the Tank move
	// To set 1g acceleration on a 40 tonnes Tank we need about 400 000 Newtons
	// Unreal base distance unit is centimeters
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float BaseMovementForce = 37500000;
};
