// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    m_springArm->SetupAttachment(RootComponent);

    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    _camera->SetupAttachment(m_springArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ATank::FireProjectile);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    m_playerTankController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!m_playerTankController)
        return;

    FHitResult hitResult;
    m_playerTankController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
    RotateTurrent(hitResult.ImpactPoint);

    // DrawDebugSphere(
    //     GetWorld(),
    //     hitResult.ImpactPoint,
    //     25.f,
    //     12,
    //     FColor::Red,
    //     false,
    //     -1.f);
}

////////////////////////////////////////////////////////////////

void ATank::Move(float value)
{
    // UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
    // FVector deltaLocation = FVector::ZeroVector;
    FVector deltaLocation = FVector::Zero();
    deltaLocation.X = value * m_speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = value * m_turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(deltaRotation, true);
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
	
}
