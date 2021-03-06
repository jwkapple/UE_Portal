// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalButton.h"

#include "Interactable.h"
#include "Components/AudioComponent.h"

// Sets default values
APortalButton::APortalButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PortalButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PB"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PB_SM(TEXT("/Game/Button/portal_button.portal_button"));
	if(PB_SM.Succeeded())
	{
		PortalButton->SetStaticMesh(PB_SM.Object);
	}

	SetRootComponent(PortalButton);
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetBoxExtent(FVector(100.0f, 100.0f, 60.0f));
	
	Box->SetCollisionProfileName(FName("Button"));
	Box->SetRelativeLocation(PortalButton->GetRelativeLocation());
	Box->SetupAttachment(PortalButton);

    Box->OnComponentBeginOverlap.AddDynamic(this, &APortalButton::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APortalButton::OnOverlapEnd);
	
	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("MATERIAL"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MM(TEXT("/Game/Button/ButtonM_Inst.ButtonM_Inst"));
	if(MM.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Material"));
		Material = MM.Object;
	}
	PortalButton->CreateDynamicMaterialInstance(0);
	
	// ---------------------- Sound ----------------------
	OnAC = CreateDefaultSubobject<UAudioComponent>(TEXT("ON"));
	OffAC = CreateDefaultSubobject<UAudioComponent>(TEXT("OFF"));
	
	static ConstructorHelpers::FObjectFinder<USoundCue> ONC(TEXT("/Game/Sound/Effects/Button/portal_button_down_01_Cue.portal_button_down_01_Cue"));
	if(ONC.Succeeded()) { OnCue = ONC.Object; OnAC->SetSound(OnCue); UE_LOG(LogTemp, Warning, TEXT("ONC Activate"));}
	

	static ConstructorHelpers::FObjectFinder<USoundCue> OFFC(TEXT("/Game/Sound/Effects/Button/portal_button_up_01_Cue.portal_button_up_01_Cue"));
	if(OFFC.Succeeded()){ OffCue = OFFC.Object; OffAC->SetSound(OffCue); UE_LOG(LogTemp, Warning, TEXT("OFFC Activate"));}
	
	
}

// Called when the game starts or when spawned
void APortalButton::BeginPlay()
{
	Super::BeginPlay();
	PortalButton->SetMaterial(0, Material);
}

// Called every frame
void APortalButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalButton::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player ON"));

	OnAC->Play();
	PortalButton->SetScalarParameterValueOnMaterials(TEXT("Activate"), 1);

	if(Receiver != nullptr)
	{
		Receiver->Interact();
	}
}

void APortalButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Player OFF"));

	OffAC->Play();
	PortalButton->SetScalarParameterValueOnMaterials(TEXT("Activate"), 0);

	if(Receiver != nullptr)
	{
		Receiver->Interact();
	}
}



