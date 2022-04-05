// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget *HUDScreen = CreateWidget(this, HUDClass);
    if (HUDScreen){
        HUDScreen->AddToViewport();
    }

}

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    // bShowMouseCursor = bPlayerEnabled;
}
