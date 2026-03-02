// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "AssetVisibilityToggle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOGBOAT_API UAssetVisibilityToggle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAssetVisibilityToggle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	USphereComponent* SphereComponent;
	
	UPROPERTY()
	UActorComponent* PlayerFogCollider;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		
};
