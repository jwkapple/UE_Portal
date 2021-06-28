// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM"));
	SetRootComponent(SMComponent);
	
	SMComponent->CreateDynamicMaterialInstance(0);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BOX_SM(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if(BOX_SM.Succeeded())
	{
		SMComponent->SetStaticMesh(BOX_SM.Object);
	}

	SMComponent->SetCollisionProfileName(FName("Portal"));
	SMComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBeginOverlap);
	SMComponent->OnComponentEndOverlap.AddDynamic(this, &APortal::OnOverlapEnd);
	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("MATERIAL"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> PORTAL_M(TEXT("/Game/Portal/Portal_M_Inst.Portal_M_Inst"));
	if(PORTAL_M.Succeeded())
	{
		Material = PORTAL_M.Object;
	}

	SMComponent->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Enter"));
}

void APortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Exit"));
}

void APortal::CreateDecal(FVector Location, FRotator Rotator, USceneComponent* HitComp)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Decal"));
	PortalDecal = UGameplayStatics::SpawnDecalAttached(Material, FVector(30.0f), HitComp, NAME_None, Location, Rotator, EAttachLocation::KeepWorldPosition);
	if(PortalDecal) UE_LOG(LogTemp, Warning, TEXT("Decal detected"));
}

