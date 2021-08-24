// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/Models/Turret/PortalTurretV2.PortalTurretV2"));
	if(SM.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM.Object);
	}

    HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HITBOX"));
	HitBox->SetBoxExtent(FVector(20.0f,20.0f, 10.0f));
	HitBox->SetRelativeLocation(StaticMesh->GetRelativeLocation() + FVector(0.0f, 0.0f, 100.0f));
	HitBox->SetCollisionObjectType(ECC_EngineTraceChannel2);

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetCollisionProfileName("Cube");
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetLinearDamping(0.005f);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::Interact()
{
	
}

