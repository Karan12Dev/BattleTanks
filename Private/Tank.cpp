// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Pawn Movement");
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		EnhancedInputComponent->BindAction(TurretRotationAction, ETriggerEvent::Triggered, this, &ATank::TurretRotation);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}


void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
	if (TankPlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MoveMappingContext, 0);
		}
	}
}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}


void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LookDebug)
	{
		if (TankPlayerController)
		{
			FHitResult HitResult;
			TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Green, false, -1.f);
		}
	}
}


void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MovementAxis = Value.Get<FVector2D>();
	
	if (TankPlayerController)
	{
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, MovementAxis.X);

		FRotator DeltaRotation = FRotator::ZeroRotator;
		if (MovementAxis.X < 0)
		{
			DeltaRotation.Yaw = -MovementAxis.Y * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
			AddActorLocalRotation(DeltaRotation, true);
		}
		else
		{
			DeltaRotation.Yaw = MovementAxis.Y * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
			AddActorLocalRotation(DeltaRotation, true);
		}
	}
}

void ATank::TurretRotation(const FInputActionValue& Value)
{
	FVector LookAxis = Value.Get<FVector>();

	if (TankPlayerController)
	{	
		FRotator ControllerRotation = GetControlRotation();
		GetTurretMesh()->SetWorldRotation(ControllerRotation);
		AddControllerYawInput(LookAxis.X);
	}
}

void ATank::Fire(const FInputActionValue& Value)
{
	Super::Fire();
}
