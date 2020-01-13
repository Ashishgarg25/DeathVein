// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicProjectile.h"
#include "WaveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API AWaveProjectile : public AMagicProjectile
{
	GENERATED_BODY()

public:

	AWaveProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UBoxComponent* WaveCollComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystemComponent* WavePS;

	UFUNCTION()
		void WaveSpawn();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
