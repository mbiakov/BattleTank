// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward declarations
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

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

	void DestroyProjectileTimerDelegate();

	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ProjectileBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent *ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 3;
};
