// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalProjectile.h"

#include "UE_PortalCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

void AUE_PortalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		
		FVector HitLocation = Hit.ImpactPoint;
		FVector HitSize(30.0f);
		FRotator HitRotation = FRotator(OtherActor->GetActorRotation() - Hit.ImpactPoint.Rotation());

		UE_LOG(LogTemp, Warning, TEXT("Roation : Roll: %f, Pitch: %f, Yaw: %f"), HitRotation.Roll, HitRotation.Pitch, HitRotation.Yaw);

		if(MyOwner->GetColor()) MyOwner->SpawnOrangePortal(HitLocation, HitRotation, Hit.GetComponent());
		else MyOwner->SpawnBluePortal(HitLocation, HitRotation, Hit.GetComponent());
		
		Destroy();
	}
}