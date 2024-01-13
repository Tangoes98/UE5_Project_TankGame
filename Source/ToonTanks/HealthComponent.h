// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// HealthComponent
	UPROPERTY(EditAnywhere)
	float m_MaxHealth = 100.f;

	float m_Health = 0.f;

	UFUNCTION()
	void DamageTaken(
		AActor *DamageActor,
		float Damage,
		const UDamageType *DamageType,
		class AController *Instigator,
		AActor *DamageCauser);
};
