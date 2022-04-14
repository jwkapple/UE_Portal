#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
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
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class UStaticMeshComponent* PortalGun;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* BlueAudioComponent;
	
	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* OrangeAudioComponent;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* GrabAudioComponent;

public:
	AUE_PortalCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = Effect)
	class UNiagaraSystem* PortalFireEffect;
	
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
	UFUNCTION()
	void SetInteractable(AInteractable* interact);
	UFUNCTION()
	bool GetInteractable() const { return IsValid(Interactable); }
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
	void OnInteract();
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
	AInteractable* Interactable;
	
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

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* GrabCue;
};

