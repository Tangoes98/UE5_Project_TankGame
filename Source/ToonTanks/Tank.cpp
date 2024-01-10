// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    _springArm->SetupAttachment(RootComponent);

    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    _camera->SetupAttachment(_springArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float value)
{
    // UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
    // FVector deltaLocation = FVector::ZeroVector;
    FVector deltaLocation = FVector::Zero();
    deltaLocation.X = value * _speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = value * _turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(deltaRotation, true);
}
