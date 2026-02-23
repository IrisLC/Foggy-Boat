// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemies/EnemyInterface.h"
#include "Enemies/Mermaid.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{

	SpawnCheckTimer = new CountdownTimer(TimeTillFirstSpawn);
	SpawnCheckTimer->OnTimerStop.AddUObject(this, &AEnemySpawner::TrySpawnEnemies);
	
	//TODO: Fill out AllEnemyTypes;
	AllEnemyTypes.Add(AMermaid::StaticClass());
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (AllEnemyTypes.Num() != 0)
	{
		AvailableEnemyTypes.Emplace(AllEnemyTypes[0]);
	}
}

void AEnemySpawner::TrySpawnEnemies()
{
	if (IsEnemySpawned && ! CanMultipleEnemies) return; // This shouldn't happen, but just in case.
	
	//The first time an enemy is attempted to be spawned it will generate a random number, after that will increase the number by 1
	if (SpawnCheckValue == -1)
	{
		//Generates a Random number by getting a number between 1-20 based on real world time
		SpawnCheckValue = 1 + FDateTime::UtcNow().GetSecond() % 20;
	} else
	{
		SpawnCheckValue++;
	}
	
	// An enemy will spawn when the CheckValue is equal to or above the To Hit value
	// Otherwise reset the timer and try again
	if (SpawnCheckValue >= ToHitInt)
	{
		SpawnEnemy();
		SpawnCheckValue = -1;
	} else
	{
		SpawnCheckTimer->Reset(TimeForSpawnValueIncrease);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	//TODO: Make Parameters relative to Boat
	
	UClass* ClassToSpawn = AvailableEnemyTypes[0].GetObject()->GetClass();
	
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters();
	SpawnParams->Name=TEXT("Mermaid");
	IEnemyInterface* CreatedEnemy = GetWorld()->SpawnActor<IEnemyInterface>(ClassToSpawn, SpawnLocation, SpawnRotation, *SpawnParams);
	
	
	IsEnemySpawned = true;
	
	ActiveEnemy = CreatedEnemy;
	ActiveEnemy->EnemyKilled.AddUObject(this, &AEnemySpawner::OnEnemyKilled);
	
}


void AEnemySpawner::OnEnemyKilled()
{
	IsEnemySpawned = false;
	SpawnCheckTimer->Reset(TimeBetweenSpawns);
}

/// <summary>
/// If there are still enemy types not in the AvailableEnemyTypes array, add the next one from the AllEnemyTypes array
/// </summary>
void AEnemySpawner::AddEnemyType()
{
	if (AllEnemyTypes.Num() != AvailableEnemyTypes.Num())
	{
		// The .Num of AvailableEnemyTypes will be equal to the index of the next enemy in AllEnemyTypes
		AvailableEnemyTypes.Emplace(AllEnemyTypes[AvailableEnemyTypes.Num()]);
	}
}

