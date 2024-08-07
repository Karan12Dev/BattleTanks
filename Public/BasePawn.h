// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	
	void HandleDestruction();


protected:
	virtual void BeginPlay() override;

	void Fire();

	UPROPERTY(BlueprintReadWrite)
	int32 Test1 = 20;
	

private:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULegacyCameraShake> DeathCameraShakeClass;


public:
	FORCEINLINE UStaticMeshComponent* GetTurretMesh() const { return TurretMesh;  }
};
