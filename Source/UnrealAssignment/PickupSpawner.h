// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.h"
#include "Components/BoxComponent.h"
#include "UnrealAssignmentCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/UObjectGlobals.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Components/InterpToMovementComponent.h"
#include "PickupSpawner.generated.h"

UCLASS()
class UNREALASSIGNMENT_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Pickups")
	TMap<TSubclassOf<APickupBase>, float> _pickups;

	//Delay after a pickup has been collected before another spawns
	UPROPERTY(EditAnywhere, Category = "Pickups")
	float _spawnDelay;

	float _totalSpawnRatio;
	APickupBase* _currentPickup;

	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* _baseMesh;

	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* _spawnLocation;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* _boxCollision;

	UPROPERTY(VisibleDefaultsOnly)
	class URotatingMovementComponent* _rotatingMove;

	UPROPERTY(VisibleDefaultsOnly)
	class UInterpToMovementComponent* _interpMove;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	void SpawnPickup();


};
