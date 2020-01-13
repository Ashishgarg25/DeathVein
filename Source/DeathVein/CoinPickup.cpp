// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DeathVeinCharacter.h"
#include "Engine.h"

ACoinPickup::ACoinPickup()
{
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	CoinMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	CoinMesh->SetupAttachment(SceneComp);

	CoinCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CoinCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	CoinCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnPickup);
	CoinCollsionComp->SetupAttachment(CoinMesh);
}

void ACoinPickup::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	Super::OnPickup(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResults);

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			UE_LOG(LogTemp, Warning, TEXT("COIN PICKED UP"));

			int CoinVal = FMath::RandRange(5, 10);

			Player->UpdateCoins(CoinVal);
			Destroy();
		}
	}
}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
