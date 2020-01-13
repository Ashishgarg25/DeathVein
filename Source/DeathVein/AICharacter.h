// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class DEATHVEIN_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	FTimerHandle DelayAttackHandler;

	UFUNCTION()
		void DelayAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Anim6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* AIMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWaypoint* NextWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> Coin;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	//	TSubclassOf<class AActor> WaveProjectile;

	UPROPERTY(EditAnywhere)
		int count;

	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		float ManaCost;

	UPROPERTY(EditAnywhere, Category = "Health")
		float CurrentHp;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Mana")
		float CurrentMana;

	UPROPERTY(EditAnywhere, Category = "Mana")
		float MaxMana;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHp();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float UpdateHp(float HpTaken);

	UFUNCTION(BlueprintPure, Category = "Mana")
		float GetCurrentMana();

	UFUNCTION(BlueprintCallable, Category = "Mana")
		float UpdateMana(float ManaTaken);

	//ATTACK
	/*UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystem* GroundSpike;

	UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystem* MeteorStrike;

	UFUNCTION()
		void Attack();

	UFUNCTION()
		void Ability1();

	UFUNCTION()
		void Ability2();

	UFUNCTION()
		void Teleport();

	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActorName;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		TSubclassOf<class UUserWidget> KillFeedWidget;

	UPROPERTY()
		class UUserWidget* CurrentKillFeedWidgetWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults);

};
