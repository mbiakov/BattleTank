// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward declarations
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANKUE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	virtual void BeginPlay() override;

	void LaunchProjectile(float LaunchSpeed);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ImpactBlast = nullptr;
};
