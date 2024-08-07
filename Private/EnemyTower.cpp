// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"



void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurret(DeltaTime);
}


void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);
}


void AEnemyTower::RotateTurret(float DeltaTime)
{
	if (InFireRange())
	{
		FVector TankLoc = Tank->GetActorLocation() - GetTurretMesh()->GetComponentLocation();
		FRotator Rotation = FRotator(0.f, TankLoc.Rotation().Yaw, 0.f);

		GetTurretMesh()->SetWorldRotation(FMath::RInterpTo(GetTurretMesh()->GetComponentRotation(), Rotation, DeltaTime, 10.f));
	}
}

bool AEnemyTower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void AEnemyTower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void AEnemyTower::CheckFireCondition()
{
	if (Tank == nullptr) return;

	if (InFireRange() && Tank->bAlive)
	{
		FireRate = FMath::RandRange(1.f, 3.f);
		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);
		Fire();
	}
}
