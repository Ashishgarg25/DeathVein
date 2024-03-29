// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicAbility.generated.h"

UCLASS()
class DEATHVEIN_API AMagicAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UBoxComponent* MagicBoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystemComponent* Ability2;

	UFUNCTION()
		void SpawnAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
