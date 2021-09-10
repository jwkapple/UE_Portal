// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalSwitch.h"

#include "PortalCube.h"
#include "Components/AudioComponent.h"

// Sets default values
APortalSwitch::APortalSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/PedestalButton/switch.switch"));
	if(SM.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM.Object);
	}

	StaticMesh->SetRelativeLocation(FVector::ZeroVector);
	StaticMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetRootComponent(StaticMesh);
	
	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("MATERIAL"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MI(TEXT("/Game/PedestalButton/PedestalButtonM_Inst.PedestalButtonM_Inst"));
	if(MI.Succeeded())
	{
		Material = MI.Object;
	}

	ClickOnSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUND_ON"));
	ClickOnSound->SetAutoActivate(false);
	
	ClickOffSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUND_OFF"));
	ClickOffSound->SetAutoActivate(false);
	
	static ConstructorHelpers::FObjectFinder<USoundCue> OnCue(TEXT("/Game/Sound/Effects/Switch/button_synth_positive_01_Cue.button_synth_positive_01_Cue"));
	if(OnCue.Succeeded())
	{
		ClickOnCue = OnCue.Object;
		ClickOnSound->SetSound(ClickOnCue);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> OffCue(TEXT("/Game/Sound/Effects/Switch/button_synth_negative_02_Cue.button_synth_negative_02_Cue"));
	if(OffCue.Succeeded())
	{
		ClickOffCue = OffCue.Object;
		ClickOffSound->SetSound(ClickOffCue);
	}
}

// Called when the game starts or when spawned
void APortalSwitch::BeginPlay()
{
	Super::BeginPlay();

	CanActivate = true;
}

void APortalSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ClickOnSound->Play();
}

void APortalSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ClickOffSound->Play();	
}

void APortalSwitch::Interact()
{
	if(CanActivate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Switch Activated"));
		ClickOnSound->Play();
		CanActivate = false;

		if(Receiver) Receiver->Interact();

		GetWorldTimerManager().SetTimer(TimeHandler, this, &APortalSwitch::SwitchActivate, 2.0f, false);
	}
}

void APortalSwitch::SwitchActivate()
{
	CanActivate = true;
	UE_LOG(LogTemp, Warning, TEXT("Switch Deactivated"));
	ClickOffSound->Play();
}

// Called every frame
void APortalSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

