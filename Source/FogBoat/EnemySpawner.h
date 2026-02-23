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
	
	UPROPERTY()
	bool CanMultipleEnemies;
	bool IsEnemySpawned;
	int ToHitInt = 15;
	int SpawnCheckValue = -1;
	
	IEnemyInterface* ActiveEnemy;
	
	TArray<TScriptInterface<IEnemyInterface>> AvailableEnemyTypes;
	TArray<TScriptInterface<IEnemyInterface>> AllEnemyTypes;
	
	UFUNCTION()
	void TrySpawnEnemies();
	void SpawnEnemy();
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnEnemyKilled();
};
