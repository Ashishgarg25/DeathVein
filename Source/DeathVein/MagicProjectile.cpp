// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DeathVeinCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComp->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
	RootComponent = BoxComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMC"));
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->MaxSpeed = 1000.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	FireBall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC"));
	FireBall->SetupAttachment(BoxComp);
	FireBall->bAutoActivate = false;

	BlackFireBall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC1"));
	BlackFireBall->SetupAttachment(BoxComp);
	BlackFireBall->bAutoActivate = false;

}

void AMagicProjectile::ParticleSpawn()
{
	ADeathVeinCharacter* player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (player->count == 2 ) {
		BlackFireBall->Activate();
	}
	else if (player->count == 1 || player->count == 3) {
		FireBall->Activate();
	}

	if (player->isLeveledUp) {
		ProjectileMovementComp->InitialSpeed += player->Agility;
		ProjectileMovementComp->MaxSpeed += player->Agility;
	}
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ParticleSpawn();
}

