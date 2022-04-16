// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LightBridge.generated.h"

UCLASS()
class UE_PORTAL_API ALightBridge : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightBridge();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Emitter;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Bridge;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* EmitterM;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TransparentWall;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* TW_M;

	bool Activate = false;
protected:

	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
private:

};
