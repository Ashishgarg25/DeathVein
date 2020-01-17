// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicAbility.h"
#include "DeathVeinCharacter.h"
#include "AICharacter.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine.h"



// Sets default values
AMagicAbility::AMagicAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MagicBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Magic Box Component"));
	MagicBoxComp->SetWorldScale3D(FVector(5.f, 5.f, .01f));
	RootComponent = MagicBoxComp;

	Ability2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC2"));
	Ability2->bAutoActivate = false;
	Ability2->SetupAttachment(MagicBoxComp);

}

void AMagicAbility::SpawnAbility()
{
	ADeathVeinCharacter* PlayerChar = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (PlayerChar->isAttacking) {
		Ability2->Activate();
		UE_LOG(LogTemp, Warning, TEXT("MagicAbility Working"));
	}
}

// Called when the game starts or when spawned
void AMagicAbility::BeginPlay()
{
	Super::BeginPlay();

	SpawnAbility();

}

// Called every frame
void AMagicAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

