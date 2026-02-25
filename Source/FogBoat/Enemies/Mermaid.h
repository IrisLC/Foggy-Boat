// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyInterface.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "FogBoat/UtilityScripts/Timers.h"
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
	
	UPROPERTY(EditDefaultsOnly)
	int Health;
	
	UPROPERTY(EditAnywhere)
	float TimeTillAttack = 15.f;
	float TimeTillDeath = 5.f;
	
	bool IsAttacking = false;
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BodyComp;
	UPROPERTY(EditAnywhere)
	USphereComponent* LHandComp;
	UPROPERTY(EditAnywhere)
	USphereComponent* RHandComp;

	UFUNCTION()
	void Attack();
	UFUNCTION()
	void Kill();
	
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitInfo);
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnKilled() override;
	
	

};
