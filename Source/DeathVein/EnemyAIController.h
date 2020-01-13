// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEATHVEIN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AEnemyAIController();

	/*FTimerHandle AbilityDelayHandler;

	UFUNCTION()
		void AbilityDelay();*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bIsPlayerDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAge = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AILoseSightRadius = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AIFieldOfView = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UAISenseConfig_Sight* SightConfig;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnPossess(APawn* Pawn) override;

	virtual FRotator GetControlRotation() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*> &DetectedPawn);


};
