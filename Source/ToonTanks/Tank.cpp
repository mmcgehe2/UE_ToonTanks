// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

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

        RotateTurret(HitResult.ImpactPoint);

        // FVector ToTarget = HitResult.ImpactPoint - TankPlayerController->GetActorLocation();
        // FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
        // TankPlayerController->SetActorRotation(LookAtRotation);
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
    // TankPlayerController->SetShowMouseCursor(true);
}

void ATank::Move(float value)
{
    AddActorLocalOffset(FVector(value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed, 0.f, 0.f), true);
}

void ATank::Turn(float value)
{

    AddActorLocalRotation(FRotator(0.f, value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate, 0.f), true);
}