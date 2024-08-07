// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"


class UInputAction;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	bool bAlive = true;


protected:
	virtual void BeginPlay() override;
	


private:
	bool LookDebug = false;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	APlayerController* TankPlayerController;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* MoveMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveAction;
	void Move(const FInputActionValue& Value);

	float TurnRate = 45.f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* TurretRotationAction;
	void TurretRotation(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* FireAction;
	void Fire(const FInputActionValue& Value);


public:
	FORCEINLINE APlayerController* GetTankPlayerController() const { return TankPlayerController;  }
};
