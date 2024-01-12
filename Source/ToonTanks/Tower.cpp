// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawSphere(m_FireRange);

    if (!m_pTank)
        return;

    float distance = FVector::Dist(GetActorLocation(), m_pTank->GetActorLocation());

    if (distance > m_FireRange)
        return;

    RotateTurrent(m_pTank->GetActorLocation());
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    m_pTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
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
