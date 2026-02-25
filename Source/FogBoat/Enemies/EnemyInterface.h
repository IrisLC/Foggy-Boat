// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FogBoat/UtilityScripts/Timers.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FOGBOAT_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEnemyInterface();
	
	DECLARE_MULTICAST_DELEGATE(EnemyKilledEvent);
	EnemyKilledEvent EnemyKilled;
protected:
	/// <summary>
	/// The timer for how long it takes for the attack to start
	/// </summary>
	CountdownTimer* AttackTimer;
	CountdownTimer* KillTimer;
	int CreatureType = -1;
public:
	void OnSpawn();
	virtual void OnKilled();
};
