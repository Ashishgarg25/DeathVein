// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DeathVeinCharacter.generated.h"

UCLASS(config=Game)
class ADeathVeinCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ADeathVeinCharacter();

	//--------------------------------CUSTOMS------------------------------------------------
	//COOLDOWN
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle CoolDownHandler;

	UFUNCTION()
		void CoolDownDelay();

	UFUNCTION()
		void CoolDownDelay1();

	UFUNCTION()
		void CoolDownDelay2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float ManaCost1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float ManaCost2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float CoolDown1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolDown")
		float CoolDown2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isItemUsed1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isItemUsed2;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		TSubclassOf<class UUserWidget> InventoryWidget;

	UPROPERTY()
		class UUserWidget* CurrentInventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		TSubclassOf<class UUserWidget> ShopWidget;

	UPROPERTY()
		class UUserWidget* CurrentShopWidget;

	//COINS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
		int CurrentCoins;

	UFUNCTION(BlueprintPure, Category = "Coins")
		int GetCurrentCoins();

	UFUNCTION(BlueprintCallable, Category = "Coins")
		int UpdateCoins(int CoinsGain);

	//HEALTH AND MANA AND RESISTANCE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance")
		int HealthResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
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

	UPROPERTY(EditAnywhere, Category = "Armor")
		bool isArmorEquipped;


	//PARTICLES SYSTEM / SPELL SYSTEM  WITH SPELL RESISTANCE

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> Fireball;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> WaveProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> StormProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<class AActor> MagicAbility;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystem* Ability1Emitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystem* Ability2Emitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystem* Ability3Emitter;*/


	//PLAYER TYPE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Intelligence;

	//LEVEL SYSTEM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Level System")
		int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Level System")
		int MaxLevel;

	UFUNCTION(BlueprintPure, Category = "Player Level System")
		int GetCurrentLvl();

	UFUNCTION(BlueprintCallable, Category = "Player Level System")
		int UpdateLvl(int XpGain);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Level System")
		int Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Level System")
		int MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Level System")
		bool isLeveledUp;

	//ANIMATION MONTAGE SECTION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Attack1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Attack2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Attack3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Ability1Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Ability2Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		class UAnimMontage* Ability3Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		bool isRollDodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		float AnimPlayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		bool isAttacking;

	//RESET ATTACK
	UPROPERTY()
		FTimerHandle ResetAttackHandler;

	UFUNCTION()
		void ResetAttack();

	//DELAY ATTACK
	UPROPERTY()
		FTimerHandle DelayHandler;

	UFUNCTION()
		void DelayAttack();

	//ABILITY SYSTEM BOOLEAN PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool isTeleporting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool isUsingAbility1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool isRegenMana = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool isUsingAbility2 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool isUsingAbility = false;

	//----------------------------------------------------------------------------------------

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	void OpenCloseShop();

	void PrimaryItemUse();

	void SecondaryItemUse();

	void OpenCloseInventory();

	void PrimaryAttack();

	void StopPrimaryAttack();

	//Abilities
	void PrimaryAbility();

	void SecondaryAbility();

	void ThirdAbility();

	void FourthAbility();

	void StartRollDodge();

	void StopRollDodge();

	void LockOn();

	void StopLockOn();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

