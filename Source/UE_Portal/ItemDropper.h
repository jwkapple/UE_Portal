// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Receiver.h"
#include "Components/BoxComponent.h"

#include "ItemDropper.generated.h"

UCLASS()
class UE_PORTAL_API AItemDropper : public AReceiver
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDropper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* Material;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Plank;
	UPROPERTY(VisibleAnywhere)
	class AActor* Box;

	UPROPERTY(VisibleAnywhere, Category = Function)
	bool isActive;

	UPROPERTY(VisibleAnywhere, Category = Plank)
	bool IsBlocking = true;

	UPROPERTY(VisibleAnywhere, Category = Cube)
	class AActor* Cube;

	UPROPERTY(VisibleAnywhere, Category = Cube)
	class AActor* NextCube;
	
	UPROPERTY(VisibleAnywhere, Category = Cube)
	FVector CubeSpawnLocation;

	UPROPERTY(VisibleAnywhere, Category = Cube)
	FRotator CubeSpawnRotation;

	FTimerHandle TimeHandler;
	
	UFUNCTION()
	void SetPlankCollision();

	UFUNCTION()
	void SpawnCube();
};
