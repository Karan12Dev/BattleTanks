// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	void ActorDied(AActor* DeadActor);


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);


private:
	void HandleGameStart(); 
	int32 GetTargetTowerCount();


	UPROPERTY()
	class ATank* Tank;

	UPROPERTY()
	class AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay = 3.f;

	int32 TargetTowers = 0;
};
