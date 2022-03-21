// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

private:

	class ATank* Tank;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 1000.f;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category = "Combat");
	float FireRate = 2.f;
	void CheckFireCondition();
	bool TankInRange();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltatTime) override;

	void HandleDestruction();
	
};
