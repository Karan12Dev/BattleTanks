// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTower : public ABasePawn
{
	GENERATED_BODY()
	

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;
	

private:
	void RotateTurret(float DeltaTime);
	bool InFireRange();

	UPROPERTY()
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	float FireRange;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
};
