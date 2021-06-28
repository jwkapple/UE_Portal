// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalProjectile.h"

#include "UE_PortalCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AUE_PortalProjectile::AUE_PortalProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUE_PortalProjectile::OnHit);		// set up a notification for when this component hits something blocking

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DECAL(TEXT("/Game/Portal/Portal_M_Inst.Portal_M_Inst"));
	if(DECAL.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DecalM Load completed"));
		DecalM = DECAL.Object;
	}
	
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	CollisionComp->CreateDynamicMaterialInstance(0);
	
	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 20.0f;
}

void AUE_PortalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		FVector HitLocation = Hit.Location + GetActorForwardVector() * 15.0f;
		FVector HitSize(30.0f);
		FRotator HitRotation = Hit.ImpactNormal.Rotation();

		if(DecalM)
		{
			UE_LOG(LogTemp, Warning, TEXT("Material Detected"));

			if(MyOwner->GetColor()) MyOwner->SpawnOrangePortal(HitLocation, HitRotation, Hit.GetComponent());
			MyOwner->SpawnBluePortal(HitLocation, HitRotation, Hit.GetComponent());
		}
		Destroy();
	}
}