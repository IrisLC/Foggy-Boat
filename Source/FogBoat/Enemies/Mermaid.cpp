// Fill out your copyright notice in the Description page of Project Settings.


#include "Mermaid.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AMermaid::AMermaid()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = Mesh;
	BodyComp = CreateDefaultSubobject<UCapsuleComponent>("Body Collider");
	BodyComp->SetupAttachment(Mesh);
	LHandComp = CreateDefaultSubobject<USphereComponent>("Left Hand Collider");
	LHandComp->SetupAttachment(Mesh);
	RHandComp = CreateDefaultSubobject<USphereComponent>("Right Hand Collider");
	RHandComp->SetupAttachment(Mesh);
	
	BodyComp->SetCollisionProfileName(TEXT("Pawn"));
	LHandComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RHandComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	
}

// Called when the game starts or when spawned
void AMermaid::BeginPlay()
{
	Super::BeginPlay();
	
	AttackTimer = new CountdownTimer(TimeTillAttack);
	AttackTimer->OnTimerStop.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(AMermaid, Attack));
	
	KillTimer = new CountdownTimer(TimeTillDeath);
	KillTimer->OnTimerStop.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(AMermaid, Kill));
	
	BodyComp->OnComponentHit.AddDynamic(this, &AMermaid::OnHit);
	
	AttackTimer->Start();
}

void AMermaid::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attacking"));
	//TODO: Add the requirements for a point of no return attack
	AttackStage = 2;
	
	// //Rotate the enemy to look at the player
	// FVector PointVector = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation() - GetActorLocation();
	// SetActorRotation(FRotationMatrix::MakeFromX(PointVector).Rotator());
	
	KillTimer->Start();
}

void AMermaid::Kill()
{
	//TODO: Initiate Game over
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	
	EndGame = true;
}

void AMermaid::OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& HitInfo)
{
	//TODO: Make sure this works properly when the oar and flare are implemented
	if (AttackStage != 2)
	{
		if (OtherActor->GetName() == "BP_Oar")
		{
			//TODO: Check oar velocity
			//float ImpactSpeed = OtherComp->GetPhysicsLinearVelocityAtPoint(HitInfo.Location).Size();
			
			//if (ImpactSpeed > MinOarSpeed)
			Health--;
			return;
		}
	}
	
	// if (OtherActor->GetName() == "Flare")
	// {
	// 	Health = 0;
	// }
}

// Called every frame
void AMermaid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AttackTimer->Tick(DeltaTime);
	KillTimer->Tick(DeltaTime);
	if (AttackStage == 0 && AttackTimer->Time <= TimeTillAttack / 2)
	{
		AttackStage = 1;
	}
	
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



