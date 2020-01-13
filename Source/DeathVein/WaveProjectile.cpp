// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DeathVeinCharacter.h"
#include "AICharacter.h"
#include "Engine.h"

ADeathVeinCharacter* MagePlayer;

AWaveProjectile::AWaveProjectile()
{
	WavePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WavePSC"));
	WavePS->SetupAttachment(BoxComp);
	WavePS->bAutoActivate = false;
}

void AWaveProjectile::BeginPlay() {
	Super::BeginPlay();

	MagePlayer = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);
}

void AWaveProjectile::WaveSpawn() {

	if (MagePlayer->count == 0) {
		WavePS->Activate();
	}
}

void AWaveProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	WaveSpawn();
}
