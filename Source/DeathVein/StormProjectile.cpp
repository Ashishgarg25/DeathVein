// Fill out your copyright notice in the Description page of Project Settings.


#include "StormProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DeathVeinCharacter.h"
#include "AICharacter.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
AStormProjectile::AStormProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component 1"));
	BoxComp->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AStormProjectile::OnOverlap1);
	RootComponent = BoxComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMCStorm"));
	ProjectileMovementComp->InitialSpeed = 500.f;
	ProjectileMovementComp->MaxSpeed = 500.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	StormPS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSCStorm"));
	StormPS->SetupAttachment(BoxComp);
	StormPS->bAutoActivate = false;
}

void AStormProjectile::StormSpawn()
{
	ADeathVeinCharacter* player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (player->isUsingAbility) {
		StormPS->Activate();
	}
}

// Called when the game starts or when spawned
void AStormProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStormProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StormSpawn();
}

//void AStormProjectile::OnOverlap1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults)
//{
//	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
//	{
//		AAICharacter* Enemy = (AAICharacter*)OtherActor;
//		Enemy->UpdateHp(30.f);
//	}
//}

