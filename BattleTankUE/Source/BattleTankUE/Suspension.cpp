// MBI Copyrights

#include "Suspension.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/World.h"


ASuspension::ASuspension() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension"));
	SetRootComponent(Suspension);

	Axis = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axis"));
	Axis->SetupAttachment(Suspension);
	Axis->SetSimulatePhysics(true);
	Axis->SetMassOverrideInKg(NAME_None, 1000);

	WheelRotationConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelRotationConstraint"));
	WheelRotationConstraint->SetupAttachment(Axis);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(WheelRotationConstraint);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 1000);
}


void ASuspension::BeginPlay() {
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASuspension::OnHit);

	SetupConstrainedComponents();
}


void ASuspension::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!ensure(GetWorld()->TickGroup == TG_PostPhysics)) return;
	ForceMagnitudeToApplyThisFrame = 0;
}


void ASuspension::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	ApplyForce();
}


void ASuspension::SetupConstrainedComponents() {
	if (!ensure(GetAttachParentActor())) return;
	UPrimitiveComponent *TankBody = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!ensure(TankBody)) return;
	Suspension->SetConstrainedComponents(TankBody, NAME_None, Axis, NAME_None);

	WheelRotationConstraint->SetConstrainedComponents(Axis, NAME_None, Wheel, NAME_None);
}


void ASuspension::AddDrivingForce(float ForceMagnitude) {
	ForceMagnitudeToApplyThisFrame = ForceMagnitudeToApplyThisFrame + ForceMagnitude;
}


void ASuspension::ApplyForce() {
	Wheel->AddForce(Axis->GetForwardVector() * ForceMagnitudeToApplyThisFrame);
}
