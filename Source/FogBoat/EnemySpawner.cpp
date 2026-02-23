// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemies/EnemyInterface.h"
#include "Enemies/Mermaid.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{

	SpawnCheckTimer = new CountdownTimer(60.f);
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
		SpawnCheckValue = 1 + FDateTime::Now().GetSecond() % 20;
	} else
	{
		SpawnCheckValue++;
	}
	
	// An enemy will spawn when the CheckValue is equal to or above the To Hit value
	// Otherwise reset the timer for 2.5 seconds and try again
	if (SpawnCheckValue >= ToHitInt)
	{
		SpawnEnemy();
		SpawnCheckValue = -1;
	} else
	{
		SpawnCheckTimer->Reset(2.5f);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	//TODO: Add Enemy Spawning
	
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

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::OnEnemyKilled()
{
	IsEnemySpawned = false;
	SpawnCheckTimer->Reset(30.f);
}

