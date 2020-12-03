// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes.h"

// Sets default values for this component's properties
UAttributes::UAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_movementSpeed = 600;
	_sprintSpeed = 1200;
}


// Called when the game starts
void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UFUNCTION(BlueprintCallable) bool UAttributes::TakeDamage(float damage)
{
	int leftOverDamage = FMath::Max(damage - _currentShield, 0.0f);
	_currentShield = FMath::Max(_currentShield - damage, 0.0f);

	if (leftOverDamage > 0) {
		_currentHealth = FMath::Max(_currentHealth - leftOverDamage, 0);
	}

	_shieldRecoverDelayTimer = _shieldRecoverDelay;

	if (_currentHealth <= 0)
		return true;
	else
		return false;
}

void UAttributes::RecoverShield(float DeltaTime)
{
	if (_currentShield < _maxShield) {
		if (_shieldRecoverDelayTimer > 0.0f) {
			_shieldRecoverDelayTimer -= DeltaTime;
		}
		else {
			_currentShield = FMath::Min((float)_maxShield, _currentShield + (_shieldRecoverRate * DeltaTime));
		}
	}
}

void UAttributes::ReplenishStamina()
{
	_stamina += _staminaRecoverRate;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Stamina = %i"), _stamina));
}

