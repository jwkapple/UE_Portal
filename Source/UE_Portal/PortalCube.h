// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PortalCube.generated.h"

UCLASS()
class UE_PORTAL_API APortalCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalCube();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
};
