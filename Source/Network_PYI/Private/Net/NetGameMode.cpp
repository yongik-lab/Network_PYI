// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/NetGameMode.h"
#include "Net/NetGameState.h"
#include "Net/NetPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "TimerManager.h"

ANetGameMode::ANetGameMode()
{
	GameStateClass = ANetGameState::StaticClass();
	PlayerStateClass = ANetPlayerState::StaticClass();
}

void ANetGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartMatchLogic();
}

void ANetGameMode::TickMatch()
{
	ANetGameState* GS = GetGameState<ANetGameState>();
	if (!GS) return;

	GS->RemainingSeconds = FMath::Max(0, GS->RemainingSeconds - 1);

	if (GS->RemainingSeconds <= 0)
	{
		FinishMatchLogic();
	}
}

void ANetGameMode::StartMatchLogic()
{
	ANetGameState* GS = GetGameState<ANetGameState>();
	if (!GS) return;

	GS->RemainingSeconds = 60;
	GS->MatchPhase = ENetMatchPhase::Playing;

	GetWorldTimerManager().SetTimer(
		MatchTimerHandle,
		this,
		&ANetGameMode::TickMatch,
		1.0f,
		true
	);

}

void ANetGameMode::FinishMatchLogic()
{
	GetWorldTimerManager().ClearTimer(MatchTimerHandle);

	ANetGameState* GS = GetGameState<ANetGameState>();
	if (!GS) return;

	GS->MatchPhase = ENetMatchPhase::Finished;

	APlayerState* P0 = (GS->PlayerArray.IsValidIndex(0)) ? GS->PlayerArray[0] : nullptr;
	APlayerState* P1 = (GS->PlayerArray.IsValidIndex(1)) ? GS->PlayerArray[1] : nullptr;

	ANetPlayerState* N0 = Cast<ANetPlayerState>(P0);
	ANetPlayerState* N1 = Cast<ANetPlayerState>(P1);

	if (N0 && N1)
	{
		if (N0->PickupCount > N1->PickupCount) GS->WinnerPlayerState = N0;
		else if (N1->PickupCount > N0->PickupCount) GS->WinnerPlayerState = N1;
		else GS->WinnerPlayerState = nullptr;
	}
}
