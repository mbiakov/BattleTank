// MBI Copyrights

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKUE_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	AActor* GetSpawnedActor() const;

private:
	UPROPERTY()
	AActor *SpawnedActor = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

	USpawnPoint();
	virtual void BeginPlay() override;
};
