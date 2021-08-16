// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalCube.h"
#include "UE_PortalCharacter.h"

// Sets default values
APortalCube::APortalCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/Cube/EDITOR_cube.EDITOR_cube"));
	if(SM.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM.Object);
	}

	SetRootComponent(StaticMesh);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HITBOX"));
	HitBox->SetBoxExtent(FVector(150.0f));

	HitBox->SetupAttachment(RootComponent);
	HitBox->SetRelativeLocation(FVector(-10.0f, -60.0f, 80.0f));
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI(TEXT("/Game/Cube/CubeM_Inst.CubeM_Inst"));
	if(MI.Succeeded())
	{
		Material = MI.Object;
	}
}

// Called when the game starts or when spawned
void APortalCube::BeginPlay()
{
	Super::BeginPlay();

	
	StaticMesh->SetMaterial(0, Material);
}

void APortalCube::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

// Called every frame
void APortalCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalCube::Grab(bool& isGrab)
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	if(!isGrab)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attach"));
		StaticMesh->SetSimulatePhysics(false);		
		AttachToComponent(MyOwner->GetMesh1P(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Grab"));
		isGrab = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Detach"));
		StaticMesh->SetSimulatePhysics(true);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SetOwner(nullptr);
		isGrab = false;
	}
}

