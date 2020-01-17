// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include"Pickups.h"
#include "DeathVeinCharacter.h"
#include "DeathVeinGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

ADeathVeinCharacter* Player1;
ADeathVeinGameMode* GameMode1;

AHealthPickup::AHealthPickup()
{
	HealthMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health Mesh Component"));
	HealthMeshComp->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	HealthMeshComp->SetupAttachment(SceneComp);

	HpCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	HpCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	HpCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnPickup);
	HpCollsionComp->SetupAttachment(HealthMeshComp);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>BlueMat(TEXT("MaterialInstanceConstant'/Game/PickupAssets/HealthColor.HealthColor'"));
	
	if (BlueMat.Succeeded()) {
		HealthMeshComp->SetMaterial(0, BlueMat.Object);
	}

	value = 1;
}

void AHealthPickup::HealthGainFromInventory()
{
	Player1 = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	GameMode1 = (ADeathVeinGameMode*)GetWorld()->GetAuthGameMode();

	/*for (int i = 0; i < 8; i++) {
		int Item = GameMode1->InventoryItems[i];

		if (Item == value) {
			Player1->CurrentHp += HpGain;
			if (Player1->CurrentHp >= 400.f) {
				Player1->CurrentHp = 400.f;
			}
			Item = 0;
			GameMode1->InventoryItems[i] = 0;
			break;
		}
	}*/

	if (Player1->isItemUsed1) {
		int Item = GameMode1->InventoryItems[0];
		if (Item == value) {
			Player1->CurrentHp += HpGain;
			if (Player1->CurrentHp >= 400.f) {
				Player1->CurrentHp = 400.f;
			}
			GameMode1->InventoryItems[0] = 0;
		}
	}
	else if (Player1->isItemUsed2) {
		int Item = GameMode1->InventoryItems[1];
		if (Item == value) {
			Player1->CurrentHp += HpGain;
			if (Player1->CurrentHp >= 400.f) {
				Player1->CurrentHp = 400.f;
			}
			GameMode1->InventoryItems[1] = 0;
		}
	}
}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	HpGain = 100.f;
}

void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = FRotator(GetActorRotation().Pitch, 150.f * DeltaTime, GetActorRotation().Roll);

	FQuat QuatRotation = FQuat(rotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	Player1 = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (Player1 != nullptr)
	{
		if (Player1->isItemUsed1 || Player1->isItemUsed2)
		{
			HealthGainFromInventory();
			//Destroy();
		}
	}
}

void AHealthPickup::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{

	Super::OnPickup(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResults);

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		Player1 = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player1) {
			UE_LOG(LogTemp, Warning, TEXT("ITEM PICKED UP"));

			GameMode1 = (ADeathVeinGameMode*)GetWorld()->GetAuthGameMode();

			for (int i = 0; i <= 7; i++) {
				if (GameMode1->InventoryItems[i] == 0) {
					GameMode1->InventoryItems[i] = value;
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