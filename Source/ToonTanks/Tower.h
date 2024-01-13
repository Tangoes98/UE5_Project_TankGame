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

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	class ATank* m_pTank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float m_FireRange = 300.f;

	void DrawSphere(float &fireRange);

	bool IsPlayerInFireRange();

	FTimerHandle m_FireRateTimerHandle;
	float m_FireRate = 2.f;
	void CheckFireCondition();

};
