// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups.h"
#include "ManaPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API AManaPickup : public APickups
{
	GENERATED_BODY()

	AManaPickup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* ManaMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* ManaCollsionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ManaGain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int value;

	UFUNCTION()
		void ManaGainFromInventory();

	virtual void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
