// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
	bReplicates = true;
}

void ANetGameState::OnRep_RemainingSeconds()
{
}

void ANetGameState::OnRep_MatchPhase()
{
}

void ANetGameState::OnRep_WinnerPlayerState()
{
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, RemainingSeconds);
	DOREPLIFETIME(ANetGameState, MatchPhase);
	DOREPLIFETIME(ANetGameState, WinnerPlayerState);
}
