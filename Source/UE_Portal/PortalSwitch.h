// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Receiver.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"

#include "PortalSwitch.generated.h"

UCLASS()
class UE_PORTAL_API APortalSwitch : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalSwitch();
	
	UPROPERTY(EditAnywhere)
	class AReceiver* Receiver = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Interact() override;
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstance* Material;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	UAudioComponent* ClickOnSound;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	UAudioComponent* ClickOffSound;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* ClickOnCue;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* ClickOffCue;

	UPROPERTY(VisibleAnywhere)
	bool CanActivate; //
	
	FTimerHandle TimeHandler;
	
	UFUNCTION()
	void SwitchActivate();
};
