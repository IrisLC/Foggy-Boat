// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetVisibilityToggle.h"

// Sets default values for this component's properties
UAssetVisibilityToggle::UAssetVisibilityToggle()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	// ...
}


// Called when the game starts
void UAssetVisibilityToggle::BeginPlay()
{
	Super::BeginPlay();

	// don't setup anything if there isn't the collider or else nothing will work
	if (PlayerFogCollider == nullptr) return;
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UAssetVisibilityToggle::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UAssetVisibilityToggle::EndOverlap);
	
	GetOwner()->SetActorHiddenInGame(true);
	
}

void UAssetVisibilityToggle::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp == PlayerFogCollider)
	{
		GetOwner()->SetActorHiddenInGame(false);
	}
}

void UAssetVisibilityToggle::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp == PlayerFogCollider)
	{
		GetOwner()->SetActorHiddenInGame(true);
	}
}


