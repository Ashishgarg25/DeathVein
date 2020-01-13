// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups.h"
#include "ArmorPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API AArmorPickup : public APickups
{
	GENERATED_BODY()

	AArmorPickup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* ArmorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* ArmorCollsionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UMaterialInterface*>ArmorMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Resistance;

	UFUNCTION()
		void ChangeColor();

	UFUNCTION()
		void ResistanceGain();

	virtual void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};


