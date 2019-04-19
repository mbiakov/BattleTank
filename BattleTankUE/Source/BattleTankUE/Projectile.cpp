// MBI Copyrights

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Classes/Kismet/GameplayStatics.h"


AProjectile::AProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Projectile Blast"));
	ProjectileBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


void AProjectile::BeginPlay() {
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit) {
	/// Destroying the mesh to prevent it taking damage in place of the Tank. The Projectile Destruction will come at the end of the method.
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	ProjectileBlast->Deactivate();
	ImpactBlast->Activate();
	UGameplayStatics::ApplyRadialDamage(this, BaseDamageAmount, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
	ExplosionForce->FireImpulse();

	/// Destroying the Projectile
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectileTimerDelegate, DestroyDelay, false);
}


void AProjectile::LaunchProjectile(float LaunchSpeed) {
	if (!ensure(ProjectileMovementComponent)) return;
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComponent->Activate();
}


void AProjectile::DestroyProjectileTimerDelegate() {
	Destroy();
}
