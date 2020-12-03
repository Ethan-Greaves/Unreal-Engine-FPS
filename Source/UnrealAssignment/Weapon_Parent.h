// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Parent.generated.h"

UCLASS()
class UNREALASSIGNMENT_API AWeapon_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable) bool GetIsFiring() { return isFiring; }

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") bool isFiring;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") int currentAmmo;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats") int maxAmmo;

};
