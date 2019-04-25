// MBI Copyrights

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


USpawnPoint::USpawnPoint() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USpawnPoint::BeginPlay() {
	Super::BeginPlay();

	if (!ensure(SpawnClass)) return;
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!ensure(SpawnedActor)) return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


AActor* USpawnPoint::GetSpawnedActor() const {
	return SpawnedActor;
}
