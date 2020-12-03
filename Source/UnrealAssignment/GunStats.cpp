// Fill out your copyright notice in the Description page of Project Settings.


#include "GunStats.h"

// Sets default values for this component's properties
UGunStats::UGunStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGunStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UFUNCTION(BlueprintCallable)USoundBase* UGunStats::GetGunSound()
{
	//***************************************************************************************************
	//Adding extra logic as these Getters are returning pointers and being nullptr causes Unreal to crash
	//***************************************************************************************************

	//If gun sound does not exist
	if (!gunSound) {
		UE_LOG(LogTemp, Warning, TEXT("gun sound not found at %s"), *(GetOwner()->GetName()))
		return nullptr;
	}
	else {
		return gunSound;
	}
}

UFUNCTION(BlueprintCallable)UParticleSystem* UGunStats::GetMuzzleFlash()
{
	if (!muzzleFlash) {
		UE_LOG(LogTemp, Warning, TEXT("muzzle flash not found at %s"), *(GetOwner()->GetName()))
		return nullptr;
	}
	else {
		return muzzleFlash;
	}
}

UFUNCTION(BlueprintCallable) bool UGunStats::SetIsFiring(bool condition)
{
	isFiring = condition;
	return UFUNCTION(BlueprintCallable) isFiring;
}

UFUNCTION(BlueprintCallable) bool UGunStats::SetIsHitscan(bool condition)
{
	isHitscan = condition;
	return UFUNCTION(BlueprintCallable) isHitscan;
}


