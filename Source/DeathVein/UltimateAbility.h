// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UltimateAbility.generated.h"

UCLASS()
class DEATHVEIN_API AUltimateAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUltimateAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UBoxComponent* MagicBoxComp1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystemComponent* Ability3;

	UFUNCTION()
		void SpawnAbility1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
