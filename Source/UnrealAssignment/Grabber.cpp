// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	reach = 300.0f;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///If physics handle is attached
	if (!physicsHandle) { return; }
	if (physicsHandle->GrabbedComponent) {
		//Move the object we are holding
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

//Look for attached physics handle component
void UGrabber::FindPhysicsHandle()
{
	//find the physics handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//if the physics handle does not exist
	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found at %s"), *(GetOwner()->GetName()))
	}
}


void UGrabber::SetupInputComponent()
{
	//Look for attached input component
	input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (input) {
		UE_LOG(LogTemp, Warning, TEXT("Input FOUND at %s"), *(GetOwner()->GetName()));
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input not found at %s"), *(GetOwner()->GetName()))
	}
}

//Log that key was pressed
void UGrabber::Grab()
{
	///Line trace and see if we hit any actors with a physics body set
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	///If we hit something, attach a physics handle
	if (actorHit) {
		if (!physicsHandle) { return; }
		physicsHandle->GrabComponent(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

//Log that key was released
void UGrabber::Released()
{
	if (!physicsHandle) { return; }
	physicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Set up Querey params 
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	///Ray cast out to reach a distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerViewPointLocation,
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	//Log collision to console
	AActor* actorHit = hit.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit->GetName()))
	}
	return hit;
}

FVector UGrabber::GetReachLineEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPointLocation, playerViewPointRotation);
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;
	return lineTraceEnd;
}
