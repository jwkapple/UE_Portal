// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropper.h"

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

	SetRootComponent(StaticMesh);
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI(TEXT("/Game/Models/ItemDropper/MI_ItemDropper.MI_ItemDropper"));
	if(MI.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDropper:: Found Material Instance"));
		Material = MI.Object;
	}

	StaticMesh->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void AItemDropper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemDropper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemDropper::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("ItemDropper:: Interact"));
}

