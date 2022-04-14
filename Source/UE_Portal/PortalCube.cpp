// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalCube.h"
#include "UE_PortalCharacter.h"
#include "Components/AudioComponent.h"

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
	StaticMesh->SetSimulatePhysics(true);
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI(TEXT("/Game/Cube/CubeM_Inst.CubeM_Inst"));
	if(MI.Succeeded())
	{
		Material = MI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(TEXT("/Game/Effects/CubeDestroy_NS.CubeDestroy_NS"));
	if(NS.Succeeded())
	{
		DestroyEffect = NS.Object;
	}
}

// Called when the game starts or when spawned
void APortalCube::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetMaterial(0, Material);
	StaticMesh->CreateDynamicMaterialInstance(0);
}

void APortalCube::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void APortalCube::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(DestroyEffect->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("CUBE DESTRUCTION"));

		FVector SpawnLocation = StaticMesh->GetComponentLocation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyEffect,SpawnLocation , FRotator::ZeroRotator);
	}
}

// Called every frame
void APortalCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalCube::Interact()
{
	auto MyOwner = Cast<AUE_PortalCharacter>(GetOwner());
	if(!MyOwner->GetInteractable())
	{
		UE_LOG(LogTemp, Warning, TEXT("PortalCube :: Attach"));

		StaticMesh->SetSimulatePhysics(false);		
		AttachToComponent(MyOwner->GetMesh1P(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Grab"));
		MyOwner->SetInteractable(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PortalCube :: Detach"));

		StaticMesh->SetSimulatePhysics(true);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		MyOwner->SetInteractable(nullptr);
		SetOwner(nullptr);
	}
}

void APortalCube::SetActivate()
{
	IsActivate = !IsActivate;
	StaticMesh->SetScalarParameterValueOnMaterials(TEXT("IsActivate"), IsActivate);
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

