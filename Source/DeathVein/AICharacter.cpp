// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DeathVeinCharacter.h"
#include "MagicAbility.h"
#include "EnemyAIController.h"
#include "Waypoint.h"
#include "Blueprint/UserWidget.h"
#include "Engine.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnOverlap);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	AIMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AI MESH COMP"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj0(TEXT("AnimMontage'/Game/Mannequin/Animations/Standing_React_Small_From_Front_Montage.Standing_React_Small_From_Front_Montage'"));
	if (MyAnimMontageObj0.Succeeded()) {
		Anim1 = MyAnimMontageObj0.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj1(TEXT("AnimMontage'/Game/Mannequin/Animations/Standing_React_Death_Backward_Montage.Standing_React_Death_Backward_Montage'"));
	if (MyAnimMontageObj1.Succeeded()) {
		Anim2 = MyAnimMontageObj1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj2(TEXT("AnimMontage'/Game/Mannequin/Animations/Injured_Stumble_Idle_Montage.Injured_Stumble_Idle_Montage'"));
	if (MyAnimMontageObj2.Succeeded()) {
		Anim3 = MyAnimMontageObj2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj3(TEXT("AnimMontage'/Game/Mannequin/Animations/Falling_Down_Montage.Falling_Down_Montage'"));
	if (MyAnimMontageObj3.Succeeded()) {
		Anim4 = MyAnimMontageObj3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj4(TEXT("AnimMontage'/Game/Mannequin/Animations/Standing_Up_Montage.Standing_Up_Montage'"));
	if (MyAnimMontageObj4.Succeeded()) {
		Anim5 = MyAnimMontageObj4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj5(TEXT("AnimMontage'/Game/Mannequin/Animations/RollLeft_Root_Montage.RollLeft_Root_Montage'"));
	if (MyAnimMontageObj5.Succeeded()) {
		Anim6 = MyAnimMontageObj5.Object;
	}
}

float AAICharacter::GetCurrentHp()
{
	return CurrentHp / MaxHp;
}

float AAICharacter::UpdateHp(float HpTaken)
{
	CurrentHp -= HpTaken;

	if (CurrentHp >= MaxHp) {
		CurrentHp = MaxHp;
	}
	else if (CurrentHp <= 0.f) {

		//PlayAnimMontage(Anim2, 1.f, NAME_None);

		ActorName = this->GetName();

		ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		Player->UpdateLvl(50);

		FVector loc = GetActorLocation();
		//loc.Z = 127.f;
		FRotator rot = GetActorRotation();

		FActorSpawnParameters SpawnParams;

		GetWorld()->SpawnActor(Coin, &loc, &rot, SpawnParams);

		SetActorHiddenInGame(true);

		if (KillFeedWidget != nullptr) {
			CurrentKillFeedWidgetWidget = CreateWidget<UUserWidget>(GetWorld(), KillFeedWidget, NAME_None);
		}

		if (CurrentKillFeedWidgetWidget != nullptr)
		{
			CurrentKillFeedWidgetWidget->AddToViewport();
		}

		GetWorld()->GetTimerManager().SetTimer(DelayDeathHandler, this, &AAICharacter::DelayDeath, 3.f, false);
	}

	return CurrentHp;
}

float AAICharacter::GetCurrentMana()
{
	return CurrentMana;
}

float AAICharacter::UpdateMana(float ManaTaken)
{
	float ManaRegen = .0002f;

	CurrentMana -= ManaTaken;
	CurrentMana += ManaRegen;

	if (CurrentMana > MaxMana) {
		CurrentMana = MaxMana;
		return CurrentMana;
	}

	else if (CurrentMana <= 0.f) {
		return CurrentMana = 0.001f;
		UE_LOG(LogTemp, Warning, TEXT("No MANA ENEMY"));
	}

	return CurrentMana;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	MaxHp = 150.f;
	CurrentHp = MaxHp;

	CurrentMana = 1.f;
	MaxMana = 200.f;
	Damage = 0.f;
	ManaCost = 0.f;

	count = 0;

	AIMesh->bHiddenInGame = true;

	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::DelayAttack()
{
	PlayAnimMontage(Anim5, 1.f, NAME_None);
}

void AAICharacter::DelayDeath()
{
	CurrentKillFeedWidgetWidget->RemoveFromParent();
	Destroy();
}

void AAICharacter::OnOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ADeathVeinCharacter* Player = (ADeathVeinCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor->ActorHasTag("MagicProjectile"))
		{
			Damage = FMath::RandRange(10.f, 20.f);
			UpdateHp(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Damage is %d"), Damage);
			PlayAnimMontage(Anim1, 1.f, NAME_None);
		}

		else if (OtherActor->ActorHasTag("WaveProjectile"))
		{
			Damage = FMath::RandRange(15.f, 25.f);
			UpdateHp(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Damage is %d"),Damage);
			PlayAnimMontage(Anim1, 1.f, NAME_None);
		}
	}
}

