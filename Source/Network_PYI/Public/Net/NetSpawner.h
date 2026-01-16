// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Net/NetPickup.h"
#include "NetSpawner.generated.h"

UCLASS()
class NETWORK_PYI_API ANetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TObjectPtr<class UBoxComponent> SpawnBox;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<class ANetPickup> PickupClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 MaxAlivePickups = 50.0f;

	FTimerHandle SpawnTimerHandle;

private:
	void SpawnPickup();

	int32 CountAlivePickups() const;

};
