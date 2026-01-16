// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_PYI_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ANetPlayerState();

	UPROPERTY(ReplicatedUsing = OnRep_PickupCount, BlueprintReadOnly, Category = "Net|Score")
	int32 PickupCount = 0;

	UFUNCTION()
	void OnRep_PickupCount();

	void AddPickup(int32 Delta);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
