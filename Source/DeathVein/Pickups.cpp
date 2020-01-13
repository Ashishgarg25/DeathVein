// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"
#include "DeathVeinCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
APickups::APickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;

	/*ArmorCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	ArmorCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	ArmorCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &APickups::OnPickup);*/
}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();
	
	isOverlapping = false;
}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickups::OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults)
{
	/*if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {

			UE_LOG(LogTemp, Warning, TEXT("ITEM PICKED UP"));
			Destroy();
		}
	}*/
}
