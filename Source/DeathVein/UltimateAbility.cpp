// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateAbility.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "DeathVeinCharacter.h"
#include "AICharacter.h"
#include "Engine.h"

// Sets default values
AUltimateAbility::AUltimateAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MagicBoxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Magic Box Component Ability 4"));
	MagicBoxComp1->SetWorldScale3D(FVector(5.f, 5.f, .01f));
	RootComponent = MagicBoxComp1;

	Ability3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC2"));
	Ability3->SetupAttachment(MagicBoxComp1);
	Ability3->bAutoActivate = false;
}

void AUltimateAbility::SpawnAbility1()
{
	ADeathVeinCharacter* PlayerChar = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (PlayerChar->isAttacking) {
		Ability3->Activate();
	}
	
}

// Called when the game starts or when spawned
void AUltimateAbility::BeginPlay()
{
	Super::BeginPlay();
	SpawnAbility1();
}

// Called every frame
void AUltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
