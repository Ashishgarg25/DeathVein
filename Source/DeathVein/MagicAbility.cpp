// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicAbility.h"
#include "DeathVeinCharacter.h"
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

	MagicCircleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magic Circle Mesh Component"));
	MagicCircleMeshComp->SetWorldLocation(FVector(0.f, 0.f, 6.f));
	MagicCircleMeshComp->SetWorldScale3D(FVector(15.f, 15.f, 15.f));
	MagicCircleMeshComp->SetupAttachment(MagicBoxComp);

	Ability2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC2"));
	Ability2->SetupAttachment(MagicBoxComp);
	Ability2->bAutoActivate = false;

	Ability3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC3"));
	Ability3->SetupAttachment(MagicBoxComp);
	Ability3->bAutoActivate = false;

}

void AMagicAbility::SpawnAbility()
{
	ADeathVeinCharacter* PlayerChar = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerPawn(this, 0);

	APlayerController* PlayerCont = (APlayerController*)UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerChar->isUsingAbility1) {

		MagicCircleMeshComp->SetHiddenInGame(false);

		FHitResult hitResult;
		bool ishit = PlayerCont->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
		if (ishit) {
			hitResult.Location.Z = -2055.f;
			this->SetActorLocation(hitResult.Location);
			//MagicCircleMeshComp->SetRelativeLocation(hitResult.Location);
		}

		if (PlayerChar->isAttacking) {
			Ability2->Activate();
			isAbilityActive1 = true;
			MagicCircleMeshComp->SetHiddenInGame(true);
		}
	}

	if (PlayerChar->isUsingAbility2) {

		MagicCircleMeshComp->SetHiddenInGame(false);

		FHitResult hitResult;
		bool ishit = PlayerCont->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
		if (ishit) {
			hitResult.Location.Z = -2055.f;
			this->SetActorLocation(hitResult.Location);
			//MagicCircleMeshComp->SetRelativeLocation(hitResult.Location);
		}

		if (PlayerChar->isAttacking) {
			Ability3->Activate();
			isAbilityActive2 = true;
			MagicCircleMeshComp->SetHiddenInGame(true);
		}
	}

}

// Called when the game starts or when spawned
void AMagicAbility::BeginPlay()
{
	Super::BeginPlay();

	MagicCircleMeshComp->SetHiddenInGame(true);

	isAbilityActive1 = false;
	isAbilityActive2 = false;
}

// Called every frame
void AMagicAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnAbility();
}

