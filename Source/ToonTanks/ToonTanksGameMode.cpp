// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GamePlayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
            GameOver(false);
        }
    }
    else if (ATower *DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowersLeft--;
        if (TargetTowersLeft <= 0){
            GameOver(true);
        }        
    }
}

void AToonTanksGameMode::BeginPlay()
{

    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowersLeft = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    
    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true);
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false);
        
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount(){
    TArray<AActor*> TargetTowers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TargetTowers);
    return TargetTowers.Num();
}