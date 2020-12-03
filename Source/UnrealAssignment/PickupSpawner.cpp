// Fill out your copyright notice in the Description page of Project Settings.
#include "PickupSpawner.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = _baseMesh;

	_boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	_boxCollision->InitBoxExtent(FVector(75.0f, 75.0f, 100.0f));
	_boxCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	_boxCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupSpawner::OnBoxBeginOverlap);
	_boxCollision->SetupAttachment(RootComponent);

	_spawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	_spawnLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	_spawnLocation->SetupAttachment(RootComponent);

	_rotatingMove = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	_rotatingMove->RotationRate.Yaw = 45.0f;

	_interpMove = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpMovement"));
	_interpMove->BehaviourType = EInterpToBehaviourType::PingPong;
	_interpMove->AddControlPointPosition(FVector::ZeroVector, true);
	_interpMove->AddControlPointPosition(FVector(0.0f, 0.0f, 15.0f), true);

	_spawnDelay = 5.0f;
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	_interpMove->SetUpdatedComponent(_spawnLocation);
	_rotatingMove->SetUpdatedComponent(_spawnLocation);

	for (auto elem : _pickups) {
		_totalSpawnRatio += elem.Value;
	}

	SpawnPickup();
	Super::BeginPlay();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupSpawner::OnBoxBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (_currentPickup != nullptr && otherActor->IsA
	(AUnrealAssignmentCharacter::StaticClass())) 
	{
		_currentPickup->OnActivate(otherActor);

		//Play particle effect

		//Play sound

		//Other cool effects

		_currentPickup->Destroy();
		_currentPickup = nullptr;

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &APickupSpawner::SpawnPickup, _spawnDelay, false);

	}
}

void APickupSpawner::SpawnPickup()
{
	if (_currentPickup == nullptr) {
		float spawnValue = FMath::FRandRange(0.0f, _totalSpawnRatio);
		float currentValue = 0.0f;

		for (auto elem : _pickups) {
			currentValue += elem.Value;
			if (spawnValue < currentValue) {
				_currentPickup = GetWorld()->SpawnActor<APickupBase>(elem.Key);
				_currentPickup->SetActorLocation(_spawnLocation->GetComponentLocation());
				_currentPickup->AttachToComponent(_spawnLocation, FAttachmentTransformRules::KeepWorldTransform);
				return;
			}
		}
	}
}

