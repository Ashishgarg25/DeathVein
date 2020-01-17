// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicDecal.generated.h"

UCLASS()
class DEATHVEIN_API AMagicDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicDecal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicCircle")
		class UStaticMeshComponent* MagicCircleMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> MagicAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> UltimateAbility;

	UFUNCTION()
		void MagicCircleSpawn();

	UFUNCTION()
		void MagicAbilityUse();

	UFUNCTION()
		void MagicAbilityUse1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
