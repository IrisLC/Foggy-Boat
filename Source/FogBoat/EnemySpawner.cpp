// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "ToolBuilderUtil.h"
#include "Enemies/EnemyInterface.h"
#include "Enemies/Mermaid.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	
	//TODO: Fill out AllEnemyTypes;
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	
	SpawnCheckTimer = new CountdownTimer(TimeTillFirstSpawn);
	SpawnCheckTimer->OnTimerStop.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(AEnemySpawner, TrySpawnEnemies));
	
	SpawnCheckTimer->Start();
	UE_LOG(LogTemp, Warning, TEXT("Timer Started"));
	
	AMermaid* MC = Cast<AMermaid>(MermaidClass);
	
	check(MC->StaticClass() == AMermaid::StaticClass());
	
	
}

void AEnemySpawner::TrySpawnEnemies()
{
	if (IsEnemySpawned && ! CanMultipleEnemies)
	{
		UE_LOG(LogTemp, Error, TEXT("You Shouldn't be here"));
		return; // This shouldn't happen, but just in case.
	}
	
	//The first time an enemy is attempted to be spawned it will generate a random number, after that will increase the number by 1
	if (SpawnCheckValue == -1)
	{
		//Generates a Random number by getting a number between 1-20 based on real world time
		SpawnCheckValue = 1 + FDateTime::UtcNow().GetSecond() % 20;
		UE_LOG(LogTemp, Warning, TEXT("Random Number is %d"), SpawnCheckValue);
	} else
	{
		SpawnCheckValue++;
		UE_LOG(LogTemp, Warning, TEXT("New Value is %d"), SpawnCheckValue);
	}
	
	// An enemy will spawn when the CheckValue is equal to or above the To Hit value
	// Otherwise reset the timer and try again
	if (SpawnCheckValue >= ToHitInt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy"));
		SpawnEnemy();
		SpawnCheckValue = -1;
	} else
	{
		SpawnCheckTimer->Reset(TimeForSpawnValueIncrease);
		SpawnCheckTimer->Start();
	}
}

void AEnemySpawner::SpawnEnemy()
{
	//TODO: Make Parameters relative to Boat
	
	
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector SpawnScale = FVector::OneVector;
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters();
	SpawnParams->Name=TEXT("Mermaid");
	
	if (PlayerBoat != nullptr)
	{
		SpawnLocation = PlayerBoat->GetActorLocation();
		SpawnRotation.Yaw += PlayerBoat->GetActorRotation().Yaw;
		
		if (FDateTime::Now().GetSecond() % 2 == 0)
		{
			//Right side spawn
			UE_LOG(LogTemp, Warning, TEXT("Right"));
			SpawnRotation.Yaw -= 90.f;
		} else
		{
			//Right side spawn
			UE_LOG(LogTemp, Warning, TEXT("Left"));
			SpawnRotation.Yaw += 90.f;
		}
		

	}
	// Will be used to check for which kind of monster is being spawned later
	AActor* CreatedEnemy;
	if (true)
	{
		AMermaid* CreatedMermaid = GetWorld()->SpawnActor<AMermaid>(MermaidClass, SpawnLocation, SpawnRotation,  *SpawnParams);
		CreatedEnemy = Cast<AActor>(CreatedMermaid);
		ActiveEnemy = CreatedMermaid;
	} 
	check(CreatedEnemy != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Spawned Mermaid"));
	
	if (PlayerBoat != nullptr)
	{
		if (FDateTime::Now().GetSecond() % 2 == 0)
		{
			CreatedEnemy->AddActorLocalOffset(FVector(-30.f,-40.f,-20.f));
		} else
		{
			CreatedEnemy->AddActorLocalOffset(FVector(-50.f,-60.f,20.f));
		}
		
		CreatedEnemy->AttachToActor(PlayerBoat, FAttachmentTransformRules::KeepWorldTransform);
		
	}
	
	IsEnemySpawned = true;
	
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
	
}

