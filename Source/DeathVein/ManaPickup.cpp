// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaPickup.h"
#include"Pickups.h"
#include "DeathVeinCharacter.h"
#include "DeathVeinGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

ADeathVeinCharacter* Player;
ADeathVeinGameMode* GameMode;

AManaPickup::AManaPickup()
{
	ManaMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mana Mesh Component"));
	ManaMeshComp->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	ManaMeshComp->SetupAttachment(SceneComp);

	ManaCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	ManaCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	ManaCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &AManaPickup::OnPickup);
	ManaCollsionComp->SetupAttachment(ManaMeshComp);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>BlueMat(TEXT("MaterialInstanceConstant'/Game/PickupAssets/ManaColor.ManaColor'"));

	if (BlueMat.Succeeded()) {
		ManaMeshComp->SetMaterial(0, BlueMat.Object);
	}

	value = 2;
}

void AManaPickup::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	Super::OnPickup(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResults);

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			UE_LOG(LogTemp, Warning, TEXT("ITEM PICKED UP"));

			GameMode = (ADeathVeinGameMode*)GetWorld()->GetAuthGameMode();

			for (int i = 0; i <= 7; i++) {
				if (GameMode->InventoryItems[i] == 0) {
					GameMode->InventoryItems[i] = value;
					UE_LOG(LogTemp, Warning, TEXT("INVENTORY ADDED SUCCESSFULLY"));

					Destroy();
					break;
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("INVENTORY FULL"));
				}
			}
		}
	}
}

void AManaPickup::ManaGainFromInventory()
{
	Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	GameMode = (ADeathVeinGameMode*)GetWorld()->GetAuthGameMode();

	for (int i = 0; i <= 7; i++) {
		int Item = GameMode->InventoryItems[i];

		if (Item == value) {
			Player->CurrentMana += ManaGain;
			if (Player->CurrentMana >= 600.f) {
				Player->CurrentMana = 600.f;
			}
			Item = 0;
			GameMode->InventoryItems[i] = 0;
			break;
		}
	}
}

void AManaPickup::BeginPlay()
{
	Super::BeginPlay();

	ManaGain = 100.f;
}

void AManaPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = FRotator(GetActorRotation().Pitch, 150.f * DeltaTime, GetActorRotation().Roll);

	FQuat QuatRotation = FQuat(rotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (Player != nullptr)
	{
		if (Player->isItemUsed1 || Player->isItemUsed2)
		{
			ManaGainFromInventory();
			Destroy();
		}
	}
	
}



