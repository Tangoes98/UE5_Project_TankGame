// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!IsPlayerInFireRange()) return;

    DrawSphere(m_FireRange);
    RotateTurrent(m_pTank->GetActorLocation());
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    m_pTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(m_FireRateTimerHandle, this, &ATower::CheckFireCondition, m_FireRate, true);
}

void ATower::DrawSphere(float &fireRange)
{
    DrawDebugSphere(
        GetWorld(),
        GetActorLocation(),
        fireRange,
        12,
        FColor::Red,
        false,
        -1.f);
}

void ATower::CheckFireCondition()
{
    
    if(!IsPlayerInFireRange()) return;

    FireProjectile();
}

bool ATower::IsPlayerInFireRange()
{
    if (!m_pTank)
        return false;

    float distance = FVector::Dist(GetActorLocation(), m_pTank->GetActorLocation());

    if (distance > m_FireRange)
        return false;

    return true;
}
