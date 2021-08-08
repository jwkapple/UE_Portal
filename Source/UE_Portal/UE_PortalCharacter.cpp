// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalCharacter.h"

#include "DrawDebugHelpers.h"
#include "UE_PortalProjectile.h"
#include "Portal.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/InputSettings.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUE_PortalCharacter

AUE_PortalCharacter::AUE_PortalCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	CameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(CameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AUE_PortalCharacter::BeginPlay()
{
	Super::BeginPlay();

	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	if(ZoomCurveFloat)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found ZoomCurveFloat"));
		
		FOnTimelineFloat ZoomTimelineProgress;
		ZoomTimelineProgress.BindUFunction(this, FName("OnZoomUpdate"));
		ZoomTimeline.AddInterpFloat(ZoomCurveFloat, ZoomTimelineProgress);
		ZoomTimeline.SetLooping(false);
	}
}

void AUE_PortalCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ZoomTimeline.TickTimeline(DeltaSeconds);
}


void AUE_PortalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("LFire", IE_Pressed, this, &AUE_PortalCharacter::OnLFire);
	PlayerInputComponent->BindAction("RFire", IE_Pressed, this, &AUE_PortalCharacter::OnRFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUE_PortalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE_PortalCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AUE_PortalCharacter::OnZoomIn);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AUE_PortalCharacter::OnZoomOut);
}

void AUE_PortalCharacter::OnZoomUpdate(float Value)
{
	float CurrentValue = FMath::Lerp(CurrentFOV, NewFOV, Value);
	CameraComponent->SetFieldOfView(CurrentValue);
}

void AUE_PortalCharacter::OnFire(bool Color)
{
	if(CheckProjectile())
	{
		if (ProjectileClass != NULL)
		{
			UWorld* const World = GetWorld();
			if (World)
			{
				const FRotator SpawnRotation = GetControlRotation();
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				ActorSpawnParams.Owner = this;

				auto projectile = World->SpawnActor<AUE_PortalProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
				Cast<AUE_PortalProjectile>(projectile)->SetColor(Color);
			}
		}

		if (FireSound != NULL)
		{
			//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		if (FireAnimation != NULL)
		{
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}	
}

void AUE_PortalCharacter::OnLFire(){ OnFire(true); }

void AUE_PortalCharacter::OnRFire(){ OnFire(false); }

void AUE_PortalCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUE_PortalCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUE_PortalCharacter::OnZoomIn()
{
	ZoomTimeline.Play();
}
void AUE_PortalCharacter::OnZoomOut()
{
	ZoomTimeline.Reverse();
}

bool AUE_PortalCharacter::CheckProjectile()
{
	FVector sLocation = GetActorLocation();
	FVector eLocation = sLocation + GetMesh()->GetForwardVector() * 100.0f;

	//UE_LOG(LogTemp, Warning, TEXT("sLocation : %f, %f, %f"), sLocation.X, sLocation.Y, sLocation.Z);
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.bTraceComplex = true;

	FHitResult HResult;
	//DrawDebugLine(GetWorld(), sLocation, eLocation, FColor::Blue, false, 100.0f, 0, 10.0f);
	if(GetWorld()->LineTraceSingleByChannel(HResult, sLocation, eLocation, ECollisionChannel::ECC_Visibility, Params))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Object Detected :: Fire Failed"));
		return false;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Fire Successded"));
	return true;
}


void AUE_PortalCharacter::SetPortal(AActor* Portal, bool Color)
{
	if(Color)
	{
		if(BluePortal)
		{
			UE_LOG(LogTemp, Warning, TEXT("BluePortal Destroy"));
			BluePortal->Destroy();
			BluePortal = NULL;
		}

		if(OrangePortal)
		{
			if(Portal->GetActorLocation() == OrangePortal->GetActorLocation())
			{
				OrangePortal->Destroy();
				OrangePortal = NULL;

				UE_LOG(LogTemp, Warning, TEXT("OrangePortal Destroyed by BlueProtal"));
			}
		}

		BluePortal = Portal;
	}
	else
	{
		if(OrangePortal) 
		{
			UE_LOG(LogTemp, Warning, TEXT("OrangePortal Destroy"));
			OrangePortal->Destroy();
			OrangePortal = NULL;
		}
		if(BluePortal)
		{
			if(BluePortal->GetActorLocation() == Portal->GetActorLocation())
			{
				BluePortal->Destroy();
				BluePortal = NULL;
	
				UE_LOG(LogTemp, Warning, TEXT("BluePortal Destroyed by OrangeProtal"));
		}
}
		OrangePortal = Portal;
	}
}

void AUE_PortalCharacter::Warp(FVector Location, FRotator Rotation)
{
	SetActorLocation(Location);
	GetController()->SetControlRotation(Rotation);
}
