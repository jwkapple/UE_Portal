// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropper.h"

#include "PortalCube.h"

// Sets default values
AItemDropper::AItemDropper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("Material"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/Models/ItemDropper/SM_ItemDropper.SM_ItemDropper"));
	if(SM.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDropper:: Found StaticMesh"));
		StaticMesh->SetStaticMesh(SM.Object);
	}

	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(StaticMesh);
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI(TEXT("/Game/Models/ItemDropper/MI_ItemDropper.MI_ItemDropper"));
	if(MI.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDropper:: Found Material Instance"));
		Material = MI.Object;
	}

	StaticMesh->SetMaterial(0, Material);

	Plank = CreateDefaultSubobject<UBoxComponent>(TEXT("Plank"));
	Plank->SetBoxExtent(FVector(60.0f, 60.0f, 3.0f));
	Plank->SetupAttachment(GetRootComponent());
	Plank->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	Plank->SetRelativeRotation(FRotator(90.0f,00.0f,0.0f));
	Plank->SetCollisionProfileName(TEXT("BlockAll"));

	
}

// Called when the game starts or when spawned
void AItemDropper::BeginPlay()
{
	Super::BeginPlay();

	CubeSpawnLocation = GetActorLocation() + FVector(0.0f, 50.0f, 40.0f);
	CubeSpawnRotation = FRotator(30.0f, 30.0f,  0.0f);
	
	Cube = GetWorld()->SpawnActor<APortalCube>(CubeSpawnLocation, CubeSpawnRotation );
}

// Called every frame
void AItemDropper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemDropper::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("ItemDropper:: Interact"));

	Cube->Destroy();
	Cube = GetWorld()->SpawnActor<APortalCube>(CubeSpawnLocation, CubeSpawnRotation);
	SetPlankCollision();

	GetWorldTimerManager().SetTimer(TimeHandler, this, &AItemDropper::SetPlankCollision, 3.0f, false);
}

void AItemDropper::SetPlankCollision()
{
	IsBlocking = !IsBlocking;
	Plank->SetCollisionProfileName(IsBlocking ? TEXT("BlockAll") : TEXT("NoCollision"));
	Cube = GetWorld()->SpawnActor<APortalCube>(CubeSpawnLocation, CubeSpawnRotation );
}

