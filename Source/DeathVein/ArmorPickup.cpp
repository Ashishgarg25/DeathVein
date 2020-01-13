// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorPickup.h"
#include"Pickups.h"
#include "DeathVeinCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

int randomColor;

AArmorPickup::AArmorPickup()
{
	ArmorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Armor Mesh Component"));
	ArmorMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	ArmorMesh->SetupAttachment(SceneComp);

	ArmorCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	ArmorCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	ArmorCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &AArmorPickup::OnPickup);
	ArmorCollsionComp->SetupAttachment(ArmorMesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>BlueMat(TEXT("MaterialInstanceConstant'/Game/PickupAssets/BlueArmor.BlueArmor'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>PurpleMat(TEXT("MaterialInstanceConstant'/Game/PickupAssets/PurpleArmor.PurpleArmor'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>GoldMat(TEXT("MaterialInstanceConstant'/Game/PickupAssets/GoldArmor.GoldArmor'"));

	ArmorMat.Add(BlueMat.Object);
	ArmorMat.Add(PurpleMat.Object);
	ArmorMat.Add(GoldMat.Object);

}

void AArmorPickup::ChangeColor()
{
	randomColor = FMath::RandRange(0, ArmorMat.Num() - 1);
	
	ArmorMesh->SetMaterial(0, ArmorMat[randomColor]);
}

void AArmorPickup::ResistanceGain()
{
	if (randomColor == 0) {
		Resistance = 10;
	}
	else if (randomColor == 1) {
		Resistance = 20;
	}
	else if (randomColor == 2) {
		Resistance = 30;
	}
	else {
		Resistance = 0;
	}
}

void AArmorPickup::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{

	Super::OnPickup(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResults);

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			UE_LOG(LogTemp, Warning, TEXT("ITEM PICKED UP"));
			Player->HealthResistance = Resistance;
			Player->isArmorEquipped = true;
			UE_LOG(LogTemp, Warning, TEXT("Resistance is %d"), Resistance);
			Destroy();
		}
	}
}

void AArmorPickup::BeginPlay()
{
	Super::BeginPlay();

	ChangeColor();
	ResistanceGain();

}

void AArmorPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = FRotator(GetActorRotation().Pitch, 150.f * DeltaTime, GetActorRotation().Roll);

	FQuat QuatRotation = FQuat(rotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}
