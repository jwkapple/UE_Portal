// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE_PortalProjectile.generated.h"

UCLASS(config=Game)
class AUE_PortalProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float LifeSpan;
public:
	AUE_PortalProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SpawnPortal(FVector SpawnLocation, FRotator SpawnRotator, FVector Normal);
	UFUNCTION()
	bool GetColor() {return Color;}
	void SetColor(bool C) { Color = C;}
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	bool Color; // true : blue, false : orange
	
};

