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

	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float LaunchSpeed);

private:
	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;
};
