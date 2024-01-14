// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_Health = m_MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	m_ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(
	AActor *DamageActor,
	float Damage,
	const UDamageType *DamageType,
	class AController *Instigator,
	AActor *DamageCauser)
{
	if (Damage <= 0.f)
		return;

	m_Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), m_Health);

	if (m_Health <= 0.f && m_ToonTanksGameMode)
	{
		m_ToonTanksGameMode->ActorDied(DamageActor);
	}
}
