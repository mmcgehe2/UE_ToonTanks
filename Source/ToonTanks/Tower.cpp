// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ATower::Tick(float DeltatTime)
{
    if(TankInRange()){
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(TankInRange()){
        Fire();
    }
}

bool ATower::TankInRange(){
if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // Check to see if the TAnk is in range
        if (Distance <= FireRange)
        {
            // If in range, return true
            return true;
        }
    }

    return false;
}