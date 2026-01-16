// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

UENUM(BlueprintType)
enum class ENetMatchPhase :uint8
{
	Waiting,
	Playing,
	Finished
};
/**
 * 
 */
UCLASS()
class NETWORK_PYI_API ANetGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANetGameState();

	UPROPERTY(ReplicatedUsing = OnRep_RemainingSeconds, BlueprintReadOnly, Category = "Net|Match")
	int32 RemainingSeconds = 60;

	UPROPERTY(ReplicatedUsing = OnRep_MatchPhase, BlueprintReadOnly, Category = "Net|Match")
	ENetMatchPhase MatchPhase = ENetMatchPhase::Waiting;

	UPROPERTY(ReplicatedUsing = OnRep_WinnerPlayerState, BlueprintReadOnly, Category = "Net|Match")
	TObjectPtr<class APlayerState> WinnerPlayerState = nullptr;

	UFUNCTION() void OnRep_RemainingSeconds();
	UFUNCTION() void OnRep_MatchPhase();
	UFUNCTION() void OnRep_WinnerPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
