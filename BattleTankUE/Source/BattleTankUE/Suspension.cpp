// MBI Copyrights

#include "Suspension.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


ASuspension::ASuspension() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension"));
	SetRootComponent(Suspension);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->AttachToComponent(Suspension, FAttachmentTransformRules::KeepRelativeTransform);
	Mass->SetSimulatePhysics(true);
	Mass->SetMassOverrideInKg(NAME_None, 10000);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Suspension, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 100);
}


void ASuspension::BeginPlay() {
	Super::BeginPlay();

	if (GetAttachParentActor()) {
		// TODO Delete the log
		UE_LOG(LogTemp, Warning, TEXT("Suspension attached to %s"), *GetAttachParentActor()->GetName());
	}
	else {
		// TODO Delete the log
		UE_LOG(LogTemp, Warning, TEXT("Suspension is not attached"));
	}
}


void ASuspension::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

