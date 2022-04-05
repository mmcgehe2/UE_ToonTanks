// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
    SpringArm->SetupAttachment(GetTurretMesh());

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
    PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::RotateTankTurret);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult);

        // RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{

    Super::HandleDestruction();

    if (DeathCameraShakeClass)
    {
        GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
    }

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    AddActorLocalOffset(FVector(Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed, 0.f, 0.f), true);
}

void ATank::Turn(float Value)
{

    AddActorLocalRotation(FRotator(0.f, Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate, 0.f), true);
}

void ATank::RotateTankTurret(float Value)
{
    GetTurretMesh()->AddLocalRotation(FRotator(0.f, Value * 5.f, 0.f), true);
}