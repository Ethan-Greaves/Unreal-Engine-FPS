// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "Attributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALASSIGNMENT_API UAttributes : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttributes();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) int GetMaxHealth() { return _maxHealth; }
	UFUNCTION(BlueprintCallable) int GetCurrentHealth() { return _currentHealth; }
	UFUNCTION(BlueprintCallable) int GetStrength() { return _strength; }
	UFUNCTION(BlueprintCallable) int GetStamina() { return _stamina; }
	UFUNCTION(BlueprintCallable) int GetMaxShield() { return _maxShield; }
	UFUNCTION(BlueprintCallable) int GetCurrentShield() { return _currentShield; }
	UFUNCTION(BlueprintCallable) float GetMovementSpeed() { return _movementSpeed; }
	UFUNCTION(BlueprintCallable) float GetSprintSpeed() { return _sprintSpeed; }
	//Returns true if current health is less than or equal to 0 after result
	UFUNCTION(BlueprintCallable) bool TakeDamage(float damage);

private:
	UPROPERTY(EditAnywhere, Category = "Stats") int _maxHealth;
	UPROPERTY(VisibleInstanceOnly, Category = "Stats") int _currentHealth;
	UPROPERTY(EditAnywhere, Category = "Stats") int _strength;
	UPROPERTY(EditAnywhere, Category = "Stats") int _stamina;
	UPROPERTY(EditAnywhere, Category = "Stats") int _staminaRecoverRate;
	UPROPERTY(EditAnywhere, Category = "Stats") int _maxShield;
	UPROPERTY(VisibleInstanceOnly, Category = "Stats") float _currentShield;
	UPROPERTY(EditAnywhere, Category = "Stats") float _shieldRecoverRate;
	UPROPERTY(EditAnywhere, Category = "Stats") float _shieldRecoverDelay;
	UPROPERTY(EditAnywhere, Category = "Stats") float _movementSpeed;
	UPROPERTY(EditAnywhere, Category = "Stats") float _sprintSpeed;

	float _shieldRecoverDelayTimer;

	void RecoverShield(float DeltaTime);

	UFUNCTION(BluePrintCallable)
	void ReplenishStamina();


};
