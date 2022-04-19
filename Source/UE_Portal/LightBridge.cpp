// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBridge.h"

// Sets default values
ALightBridge::ALightBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Emitter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EMITTER"));
	SetRootComponent(Emitter);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EMIT(TEXT("/Game/tmp/Light_bridge_emitter.Light_bridge_emitter"));
	if(EMIT.Succeeded())
	{
		Emitter->SetStaticMesh(EMIT.Object);
	}
	
	Emitter->SetCollisionProfileName(TEXT("NoCollision"));
	Emitter->CreateDynamicMaterialInstance(0);

	SetRootComponent(Emitter);
	EmitterM = CreateDefaultSubobject<UMaterialInstance>(TEXT("EMITTER_M"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EMIT_M(TEXT("/Game/tmp/LightBridgeM_Inst.LightBridgeM_Inst"));
	if(EMIT_M.Succeeded())
	{
		EmitterM = EMIT_M.Object;
	}


	Emitter->SetMaterial(0, EmitterM);
	
	TransparentWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TRANSPARENTWALL"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if(SM.Succeeded())
	{
		TransparentWall->SetStaticMesh(SM.Object);
	}
	
	TransparentWall->SetupAttachment(GetRootComponent());
	TransparentWall->SetCollisionProfileName(TEXT("NoCollision"));

	TW_M = CreateDefaultSubobject<UMaterialInstance>(TEXT("TW_M"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> TW(TEXT("/Game/tmp/LightBridge_M_Inst.LightBridge_M_Inst"));
	if(TW.Succeeded())
	{
		TW_M = TW.Object;
	}

	TransparentWall->CreateDynamicMaterialInstance(0);
	TransparentWall->SetMaterial(0, TW_M);
}

void ALightBridge::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

// Called when the game starts or when spawned
void ALightBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightBridge::Interact()
{
	Super::Interact();

	UE_LOG(LogTemp, Warning, TEXT("LIGHTBRIDGE INTERACT"));

	Activate = !Activate;
	if(Activate)
	{
		TransparentWall->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}
	else
	{
		TransparentWall->SetCollisionProfileName(TEXT("NoCollision"));
	}
	
	TransparentWall->SetScalarParameterValueOnMaterials(TEXT("Activate"), Activate);
	
	
	FVector sLocation = GetActorLocation();
	FVector eLocation = sLocation + GetRootComponent()->GetForwardVector() * 5000.0f;
	
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.bTraceComplex = true;

	FHitResult HResult;

	if(GetWorld()->LineTraceSingleByChannel(HResult, sLocation, eLocation, ECollisionChannel::ECC_Visibility, Params))
	{
		UE_LOG(LogTemp, Warning, TEXT("LightBridge Object Detected"));
	
	}
}

