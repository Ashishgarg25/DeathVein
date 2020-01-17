// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "DeathVeinCharacter.h"
#include "AICharacter.h"
#include "MagicProjectile.h"
#include "WaveProjectile.h"
#include "MagicAbility.h"
#include "Waypoint.h"
#include "Engine.h"

AAICharacter* EnemyChar;

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("My Perception Comp")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	//aiWait = true;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyChar = Cast<AAICharacter>(GetPawn());

	bIsPlayerDetected = false;
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DistanceToPlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}

	/*if (EnemyChar->NextWaypoint != nullptr && bIsPlayerDetected == false)
	{
		MoveToActor(EnemyChar->NextWaypoint, 5.0f);
	}*/
}

void AEnemyAIController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
}

FRotator AEnemyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(.0f, .0f, .0f);
	}

	return FRotator(.0f, GetPawn()->GetActorRotation().Yaw, .0f);
}

void AEnemyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawn)
{
	for (size_t i = 0; i < DetectedPawn.Num(); i++)
	{
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawn[i]);
	}

	bIsPlayerDetected = true;
}
