// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyInterface.h"
#include "GameFramework/Pawn.h"
#include "Mermaid.generated.h"

UCLASS()
class FOGBOAT_API AMermaid : public APawn, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMermaid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
