// Fill out your copyright notice in the Description page of Project Settings.


#include "Mermaid.h"

// Sets default values
AMermaid::AMermaid()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMermaid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMermaid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMermaid::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

