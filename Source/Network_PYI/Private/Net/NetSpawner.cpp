// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ANetSpawner::ANetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;

	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = false;
}

// Called when the game starts or when spawned
void ANetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&ANetSpawner::SpawnPickup,
			SpawnInterval,
			true
		);
	}
}

// Called every frame
void ANetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetSpawner::SpawnPickup()
{
	if (!HasAuthority() || !PickupClass) return;

	if (MaxAlivePickups > 0 && CountAlivePickups() >= MaxAlivePickups)
	{
		return;
	}

	const FVector Origin = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();

	const FVector SpawnLoc = Origin + FVector(
		FMath::FRandRange(-Extent.X, Extent.X),
		FMath::FRandRange(-Extent.Y, Extent.Y),
		FMath::FRandRange(-Extent.Z, Extent.Z)
	);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(PickupClass, SpawnLoc, FRotator::ZeroRotator, Params);
}

int32 ANetSpawner::CountAlivePickups() const
{
	if (!PickupClass) return 0;

	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PickupClass.Get(), Found);
	return Found.Num();
}

