// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "Particles/ParticleSystem.h"
#include "GunStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALASSIGNMENT_API UGunStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//Getters
	UFUNCTION(BlueprintCallable) bool GetIsFiring() { return isFiring; }
	UFUNCTION(BlueprintCallable) bool GetIsHitscan() { return isHitscan; }
	UFUNCTION(BlueprintCallable) bool GetGrabber() { return isGrabber; }
	UFUNCTION(BlueprintCallable) int GetCurrentAmmo() { return currentAmmo; }
	UFUNCTION(BlueprintCallable) int GetMaxAmmo() { return maxAmmo; }
	UFUNCTION(BlueprintCallable) int GetMagSize() { return magSize; }
	UFUNCTION(BlueprintCallable) float GetFireRate() { return fireRate; }
	UFUNCTION(BlueprintCallable) USoundBase* GetGunSound();
	UFUNCTION(BlueprintCallable) UParticleSystem* GetMuzzleFlash();

	//Setters
	UFUNCTION(BlueprintCallable) bool SetIsFiring(bool condition);
	UFUNCTION(BlueprintCallable) bool SetIsHitscan(bool condition);

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") bool isFiring;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") bool isHitscan;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") bool isGrabber;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") int currentAmmo;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") int maxAmmo;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") int magSize;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") float fireRate;

	UPROPERTY(EditAnywhere, Category = "Weapon Effects") USoundBase* gunSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Weapon Effects") UParticleSystem* muzzleFlash = nullptr;
};
