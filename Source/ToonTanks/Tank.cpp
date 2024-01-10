// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    _springArm->SetupAttachment(RootComponent);

    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    _camera->SetupAttachment(_springArm);



}
