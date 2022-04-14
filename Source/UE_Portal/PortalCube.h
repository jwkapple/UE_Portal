// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PortalCube.generated.h"

class USoundCue;
UCLASS()
class UE_PORTAL_API APortalCube : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalCube();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	void SetActivate();
	
	UFUNCTION()
	void Grab(bool& isGrab);
private:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	
	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* Material;

	UPROPERTY(VisibleAnywhere, Category = Util)
	bool IsGrab;

	UPROPERTY(VisibleAnywhere)
	bool IsActivate;
};
