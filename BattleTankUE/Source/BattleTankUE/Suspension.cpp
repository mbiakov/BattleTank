// MBI Copyrights

#include "Suspension.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


ASuspension::ASuspension() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	SetupConstrainedComponents();
}


void ASuspension::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void ASuspension::SetupConstrainedComponents() {
	if (!ensure(GetAttachParentActor())) return;
	UPrimitiveComponent *TankBody = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!ensure(TankBody)) return;
	Suspension->SetConstrainedComponents(TankBody, NAME_None, Axis, NAME_None);

	WheelRotationConstraint->SetConstrainedComponents(Axis, NAME_None, Wheel, NAME_None);
}

