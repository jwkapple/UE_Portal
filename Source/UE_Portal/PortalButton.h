// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"

#include "PortalButton.generated.h"

UCLASS()
class UE_PORTAL_API APortalButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalButton();

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
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PortalButton;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* OnAC;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	class UAudioComponent* OffAC;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* Material;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* OnCue;
	
	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* OffCue;
	
};
