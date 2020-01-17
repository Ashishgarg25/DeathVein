// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicDecal.h"
#include "DeathVeinCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"

// Sets default values
AMagicDecal::AMagicDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MagicCircleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magic Circle Mesh Component"));
	MagicCircleMeshComp->SetWorldLocation(FVector(0.f, 0.f, 6.f));
	MagicCircleMeshComp->SetWorldScale3D(FVector(15.f, 15.f, 15.f));
}

void AMagicDecal::MagicCircleSpawn()
{
	//Using Magic Circle
	APlayerController* PlayerCont = (APlayerController*)UGameplayStatics::GetPlayerController(this, 0);

	ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

	if (Player->isUsingAbility1 || Player->isUsingAbility2) {

		MagicCircleMeshComp->SetHiddenInGame(false);

		FHitResult hitResult;
		bool ishit = PlayerCont->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
		if (ishit) {
			hitResult.Location.Z = Player->GetActorLocation().Z;
			this->SetActorLocation(hitResult.Location);
			//MagicCircleMeshComp->SetRelativeLocation(hitResult.Location);
		}

	}
	/*else if (Player->isUsingAbility2) {

		MagicCircleMeshComp->SetHiddenInGame(false);

		FHitResult hitResult;
		bool ishit = PlayerCont->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
		if (ishit) {
			hitResult.Location.Z = Player->GetActorLocation().Z;
			this->SetActorLocation(hitResult.Location);
			MagicCircleMeshComp->SetRelativeLocation(hitResult.Location);
		}
		
	}*/
	else {
		MagicCircleMeshComp->SetHiddenInGame(true);
	}
	
}

void AMagicDecal::MagicAbilityUse()
{
	FVector loc = MagicCircleMeshComp->RelativeLocation;

	FRotator rot = MagicCircleMeshComp->RelativeRotation;

	FActorSpawnParameters SpawnParams;

	GetWorld()->SpawnActor(MagicAbility, &loc, &rot, SpawnParams);

	MagicCircleMeshComp->SetHiddenInGame(true);
	
}

void AMagicDecal::MagicAbilityUse1()
{
	FVector loc = MagicCircleMeshComp->RelativeLocation;

	FRotator rot = MagicCircleMeshComp->RelativeRotation;

	FActorSpawnParameters SpawnParams;

	GetWorld()->SpawnActor(UltimateAbility, &loc, &rot, SpawnParams);

	MagicCircleMeshComp->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void AMagicDecal::BeginPlay()
{
	Super::BeginPlay();

	MagicCircleMeshComp->SetHiddenInGame(true);
}

// Called every frame
void AMagicDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MagicCircleSpawn();
}

