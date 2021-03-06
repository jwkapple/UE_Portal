// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Portal.generated.h"

UCLASS()
class UE_PORTAL_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;
	
	UPROPERTY(EditAnywhere, Category = StaticMesh)
	UStaticMeshComponent* SMComponent;

	UPROPERTY(EditAnywhere, Category = Material)
	UMaterialInstance* Material;

	UPROPERTY(VisibleAnywhere, Category = Portal)
	FRotator Normal;
	
	UPROPERTY(VisibleAnywhere, Category = Portal)
	bool Color;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	UAudioComponent* EnterSound;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundCue* EnterBGMCue;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UNiagaraSystem* SpawnEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = Effect)
	UNiagaraComponent* SpawnEffectComponent;
	
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetNormal(FRotator NewNormal) { this->Normal = NewNormal;}
	UFUNCTION()
	FRotator GetNormal() const {return Normal;}
};
