// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups.h"
#include "CoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API ACoinPickup : public APickups
{
	GENERATED_BODY()
	
public:
	ACoinPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* CoinMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CoinCollsionComp;

	virtual void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
