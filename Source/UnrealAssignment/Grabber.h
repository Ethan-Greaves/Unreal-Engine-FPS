// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Gameframework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALASSIGNMENT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetupInputComponent();
	void FindPhysicsHandle();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float reach;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* input = nullptr;
	//Get player viewpoint
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	void Grab();
	void Released();
	const FHitResult GetFirstPhysicsBodyInReach();
	FVector GetReachLineEnd();
};
