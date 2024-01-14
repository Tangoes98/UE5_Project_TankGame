// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);
}

void ABasePawn::HandleDestruction()
{
	// Visual/ Sound effects
	
}

void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	FVector toTarget = LookAtTarget - TurrentMesh->GetComponentLocation();
	FRotator lookAtRotation = toTarget.Rotation();
	lookAtRotation.Pitch = 0.f;
	lookAtRotation.Roll = 0.f;

	TurrentMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurrentMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.f));
}

void ABasePawn::FireProjectile()
{
	FVector _ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator _ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	auto _Projectile = GetWorld()->SpawnActor<AProjectile>(m_ProjectileClass, _ProjectileSpawnPointLocation, _ProjectileSpawnPointRotation);
	_Projectile -> SetOwner(this);
	
	// DrawDebugSphere(
	// 	GetWorld(),
	// 	ProjectileSpawnPointLocation,
	// 	25.f,
	// 	12,
	// 	FColor::Green,
	// 	false,
	// 	3.f);
}

// // Called when the game starts or when spawned
// void ABasePawn::BeginPlay()
// {
// 	Super::BeginPlay();
// }

// Called every frame
// void ABasePawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

// Called to bind functionality to input
// void ABasePawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }
