// Fill out your copyright notice in the Description page of Project Settings.


#include "Mermaid.h"

// Sets default values
AMermaid::AMermaid()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackTimer = new CountdownTimer(TimeTillAttack);
	AttackTimer->OnTimerStop.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(AMermaid, Attack));
	
	KillTimer = new CountdownTimer(TimeTillDeath);
	KillTimer->OnTimerStop.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(AMermaid, Kill));
	
	BodyComp = CreateDefaultSubobject<UCapsuleComponent>("Body Collider");
	BodyComp->SetupAttachment(RootComponent);
	LHandComp = CreateDefaultSubobject<USphereComponent>("Left Hand Collider");
	LHandComp->SetupAttachment(RootComponent);
	RHandComp = CreateDefaultSubobject<USphereComponent>("Right Hand Collider");
	RHandComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMermaid::BeginPlay()
{
	Super::BeginPlay();
	
	BodyComp->OnComponentHit.AddDynamic(this, &AMermaid::OnHit);
	
	AttackTimer->Start();
}

void AMermaid::Attack()
{
	//TODO: Add the requirements for a point of no return attack
	IsAttacking = true;
	
	KillTimer->Start();
}

void AMermaid::Kill()
{
	//TODO: Initiate Game over
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
}

void AMermaid::OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& HitInfo)
{
	//TODO: Make sure this works properly when the oar and flare are implemented
	if (!IsAttacking)
	{
		if (OtherActor->GetName() == "Oar")
		{
			//TODO: Check oar velocity
			Health--;
			return;
		}
	}
	
	if (OtherActor->GetName() == "Flare")
	{
		Health = 0;
	}
}

// Called every frame
void AMermaid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Health <= 0)
	{
		OnKilled();
	}
}


void AMermaid::OnKilled()
{
	EnemyKilled.Broadcast();
	
	AttackTimer->Stop();
	KillTimer->Stop();
	
	//TODO: Play death animation and destroy enemy
}



