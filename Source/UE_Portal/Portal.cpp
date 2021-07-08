// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"


#include "DrawDebugHelpers.h"
#include "UE_PortalCharacter.h"
#include "UE_PortalProjectile.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"\

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM"));
	SetRootComponent(SMComponent);
	
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BOX_SM(TEXT("/Game/Geometry/Meshes/Shape_Plane.Shape_Plane"));
	if(BOX_SM.Succeeded())
	{
		SMComponent->SetStaticMesh(BOX_SM.Object);
	}

	SMComponent->SetWorldScale3D(FVector(2.0f, 1.5f, 1.0f));
	SMComponent->SetCollisionProfileName(FName("Portal"));
	SMComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBeginOverlap);
	SMComponent->OnComponentEndOverlap.AddDynamic(this, &APortal::OnOverlapEnd);
	
	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("MATERIAL"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> PORTAL_M(TEXT("/Game/Portal/Portal_M_Inst1.Portal_M_Inst1"));
	if(PORTAL_M.Succeeded())
	{
		Material = PORTAL_M.Object;
	}

	SMComponent->SetMaterial(0, Material);
	SMComponent->CreateDynamicMaterialInstance(0);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	auto MyOwner = Cast<AUE_PortalProjectile>(GetOwner());
	Color = MyOwner->GetColor();
	SMComponent->SetScalarParameterValueOnMaterials(FName("Color"), Color);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::BeginDestroy()
{
	Super::BeginDestroy();
}

void APortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Enter"));

	FVector WarpLocation;
	FRotator WarpRotator;
	APortal* Portal;
	
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());

	if(MyOwner->HasPortal())
	{
		if(Color)	Portal = Cast<APortal>(MyOwner->GetOrangePortal());
		else		Portal = Cast<APortal>(MyOwner->GetBluePortal());
		
		WarpLocation = Portal->GetActorLocation() + Portal->GetNormal().Vector() * 100.0f;
		WarpRotator = Portal->GetNormal();
		
		MyOwner->Warp(WarpLocation, WarpRotator);

		DrawDebugLine(GetWorld(), Portal->GetActorLocation(), Portal->GetActorLocation() + Portal->GetNormal().Vector() * 100.0f, FColor::Red, false, 10.0f, 0, 5.0f);
	}
}

void APortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Exit"));
}