// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

ANetPlayerState::ANetPlayerState()
{
	bReplicates = true;
}

void ANetPlayerState::OnRep_PickupCount()
{
}

void ANetPlayerState::AddPickup(int32 Delta)
{
	PickupCount += Delta;
	OnRep_PickupCount();
}

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, PickupCount);
}
