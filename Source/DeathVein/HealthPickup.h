// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API AHealthPickup : public APickups
{
	GENERATED_BODY()

	AHealthPickup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* HealthMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* HpCollsionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HpGain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int value;

	UFUNCTION()
		void HealthGainFromInventory();

	virtual void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
