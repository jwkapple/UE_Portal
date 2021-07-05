// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalProjectile.h"

#include "DrawDebugHelpers.h"
#include "UE_PortalCharacter.h"
#include "Portal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AUE_PortalProjectile::AUE_PortalProjectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUE_PortalProjectile::OnHit);		

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	CollisionComp->CreateDynamicMaterialInstance(0);
	

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 20.0f;

	Color = true;
}

void AUE_PortalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		
		FVector HitLocation = OtherActor->GetActorLocation() + Hit.ImpactNormal * 128.0f;
		FRotator SpawnRotation = FRotator(Hit.ImpactNormal.Rotation().Pitch + 90.0f, Hit.ImpactNormal.Rotation().Yaw + 180.0f,
			0.0f);

		SpawnPortal(HitLocation, SpawnRotation);

		Destroy();
	}
}

void AUE_PortalProjectile::SpawnPortal(FVector SpawnLocation, FRotator SpawnRotator)
{
	FActorSpawnParameters Param;
	Param.Owner = this;

	auto Portal = GetWorld()->SpawnActor<APortal>(SpawnLocation, SpawnRotator, Param);

	Cast<AUE_PortalCharacter>(GetOwner())->SetPortal(Portal, Color);
	Portal->SetOwner(GetOwner());
}

