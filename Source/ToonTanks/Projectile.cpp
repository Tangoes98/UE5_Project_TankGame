// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = m_ProjectileMesh;

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Mvoement Component"));
	m_ProjectileMovementComponent->MaxSpeed = 1300.f;
	m_ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(
	UPrimitiveComponent *HitComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	FVector NormalImpulse,
	const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
}
