// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundCue.h"

#include "UE_PortalCharacter.generated.h"

#define BLUE true
#define ORANGE false

class UInputComponent;

UCLASS(config=Game)
class AUE_PortalCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* BlueAudioComponent;
	
	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* OrangeAudioComponent;

public:
	AUE_PortalCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AUE_PortalProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UFUNCTION()
	void SetPortal(AActor* Portal, bool Color);
	UFUNCTION()
	void Warp(FVector Location, FRotator Rotation);
	UFUNCTION()
	AActor* GetBluePortal() const {return BluePortal;}
	UFUNCTION()
	AActor* GetOrangePortal() const {return OrangePortal;}
	UFUNCTION()
	bool HasPortal() const { return BluePortal && OrangePortal;}
protected:

	void OnFire(bool Color);
	void OnLFire();
	void OnRFire();
	
	void MoveForward(float Val);

	void MoveRight(float Val);

	UFUNCTION()
	void OnZoomIn();
	UFUNCTION()
	void OnZoomOut();
	UFUNCTION()
	void OnGrab();
	UFUNCTION()
	bool CheckProjectile();
protected:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:

	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	UPROPERTY(EditAnywhere, Category = CameraSettings)
	UCurveFloat* ZoomCurveFloat;
private:

	UPROPERTY(VisibleAnywhere, Category = Portal)
	AActor* BluePortal;

	UPROPERTY(VisibleAnywhere, Category = Portal)
	AActor* OrangePortal;

	UPROPERTY(VisibleAnywhere, Category = Util)
	TWeakObjectPtr<AActor> Grabing;
	
	FTimeline ZoomTimeline;

	UFUNCTION()
	void OnZoomUpdate(float Value);

	UPROPERTY(EditAnywhere, Category = CameraOptions)
	float CurrentFOV;

	UPROPERTY(EditAnywhere, Category = CameraOptions)
	float NewFOV;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* BlueCue;
	
	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* OrangeCue;

	UPROPERTY(VisibleAnywhere, Category = Util)
	bool IsGrabing;
};

