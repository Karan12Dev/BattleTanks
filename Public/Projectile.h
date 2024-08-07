// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere, Category = "Projectile Properties")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	float Damage = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULegacyCameraShake> HitCameraShakeClass;
};
