// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "EnemyTower.h"
#include "ToonTankPlayerController.h"


void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (AEnemyTower* DestroyedEnemyTower = Cast<AEnemyTower>(DeadActor))
	{
		DestroyedEnemyTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}


void AToonTankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void AToonTankGameModeBase::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	TargetTowers = GetTargetTowerCount();
	StartGame();

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 AToonTankGameModeBase::GetTargetTowerCount()
{
	TArray<AActor*> EnemyTowers;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyTower::StaticClass(), EnemyTowers);

	return EnemyTowers.Num();
}
