// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBridge.h"

// Sets default values
ALightBridge::ALightBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Emitter = CreateDefaultSubobject<UStaticMeshComponent>("EMITTER");
	static ConstructorHelpers::FObjectFinder<UStaticMeshComponent> EMIT(TEXT("/Game/tmp/Light_bridge_emitter.Light_bridge_emitter"));
	if(EMIT.Succeeded())
	{
		Emitter = EMIT.Object;
	}

	SetRootComponent(Emitter);
	
	EmitterM = CreateDefaultSubobject<UMaterialInstance>("EMITTER");
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EMIT_M(TEXT("/Game/tmp/LightBridgeM_Inst.LightBridgeM_Inst"));
	if(EMIT_M.Succeeded())
	{
		EmitterM = EMIT_M.Object;
	}

	Emitter->CreateDynamicMaterialInstance(0);
	Emitter->SetMaterial(0, EmitterM);
}

void ALightBridge::PostInitializeComponents()
{
	
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

