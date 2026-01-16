// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetPickup.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Net/NetPlayerState.h"

// Sets default values
ANetPickup::ANetPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetSphereRadius(60.0f);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;
	SetReplicateMovement(true);


}

// Called when the game starts or when spawned
void ANetPickup::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ANetPickup::OnOverlap);
	
}

// Called every frame
void ANetPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetPickup::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	ACharacter* Char = Cast<ACharacter>(OtherActor);
	if (!Char) return;

	ANetPlayerState* PS = Char->GetPlayerState<ANetPlayerState>();
	if (!PS)return;

	PS->AddPickup(1);
	Destroy();
}

