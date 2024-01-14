// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UStaticMeshComponent *m_ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UProjectileMovementComponent *m_ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UParticleSystemComponent *m_TrailParticles;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	UPROPERTY(EditAnywhere)
	float m_Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UParticleSystem *m_HitParticles;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class USoundBase *m_LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class USoundBase *m_HitSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf< class UCameraShakeBase> m_HitCameraShakeClass;
};
