// MBI Copyrights

#include "Suspension.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


ASuspension::ASuspension()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetSimulatePhysics(true);
	Mass->SetMassOverrideInKg(NAME_None, 10000);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Mass, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 100);

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension"));
	Suspension->AttachToComponent(Mass, FAttachmentTransformRules::KeepRelativeTransform);
}


void ASuspension::BeginPlay()
{
	Super::BeginPlay();
}


void ASuspension::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

