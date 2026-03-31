// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyInterface.h"
#include "GameFramework/Actor.h"
#include "UtilityScripts/Timers.h"
#include "EnemySpawner.generated.h"


UCLASS()
class FOGBOAT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	CountdownTimer* SpawnCheckTimer;

	/// <summary>
	/// The time until the first spawn check occurs
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float TimeTillFirstSpawn = 60.f;
	/// <summary>
	/// The time between incrementing a missed SpawnValue
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float TimeForSpawnValueIncrease = 2.5f;
	/// <summary>
	/// The Time from an enemy being killed to another spawn check
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float TimeBetweenSpawns = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool CanMultipleEnemies;
	bool IsEnemySpawned;
	/// <summary>
	/// The number that must be hit or exceeded for an enemy to spawn
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Parameters")
	int ToHitInt = 15;
	int SpawnCheckValue = -1;
	
	IEnemyInterface* ActiveEnemy;
	
	UFUNCTION()
	void TrySpawnEnemies();
	void SpawnEnemy();
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	AActor* PlayerBoat;
	
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TSubclassOf<AActor> MermaidClass;
public:	

	void OnEnemyKilled();
	UFUNCTION(BlueprintCallable)
	void AddEnemyType();
};
