// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalProjectile.h"

#include "DrawDebugHelpers.h"
#include "UE_PortalCharacter.h"
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
}

void AUE_PortalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		
		FVector HitLocation = Hit.ImpactPoint;
		FVector HitSize(30.0f);
		FRotator HitRotation = FRotator(Hit.ImpactNormal.Rotation().Pitch, Hit.ImpactNormal.Rotation().Yaw,
			Dot3(FVector4(Hit.ImpactNormal, 0.0f), FVector4(GetActorRightVector(), 0.0f)));
		DrawDebugLine(GetWorld(), HitLocation, HitLocation + Hit.ImpactNormal * 500.0f, FColor::Red,false,10.0f, 0, 10.0f);
		UE_LOG(LogTemp, Warning, TEXT("Roation : Roll: %f, Pitch: %f, Yaw: %f"), HitRotation.Roll, HitRotation.Pitch, HitRotation.Yaw);

		if(MyOwner->GetColor()) MyOwner->SpawnOrangePortal(HitLocation, HitRotation, Hit.GetComponent());
		else MyOwner->SpawnBluePortal(HitLocation, HitRotation, Hit.GetComponent());
		
		Destroy();
	}
}