// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "HealthSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALASSIGNMENT_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthSystem();

	UFUNCTION(BluePrintCallable, Category="Health")
		void ReplenishHealth();

	UFUNCTION(BluePrintCallable, Category = "Health")
		float GetPlayerHealth();

	UPROPERTY(EditAnywhere)
	float healing = 200.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float playerHealth = 100.0f;
	
};
