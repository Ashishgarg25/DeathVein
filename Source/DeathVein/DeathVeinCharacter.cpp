// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DeathVeinCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "StormProjectile.h"
#include "MagicAbility.h"
#include "UltimateAbility.h"
#include "MagicDecal.h"
#include "Engine.h"

//////////////////////////////////////////////////////////////////////////
// ADeathVeinCharacter

bool isLooking = false;
bool isInventoryOpen = false;
bool isShopOpen = false;

//ATTACK VARIABLES
bool isSimpleAttacking1 = false;
bool isSimpleAttacking2 = false;
bool isSimpleAttacking3 = false;
bool isSimpleAttacking4 = false;

bool isAttacking1 = false;
bool isAttacking2 = false;
bool isAttacking3 = false;
bool isAttacking4 = false;

AMagicDecal* newDecal;

ADeathVeinCharacter::ADeathVeinCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//-----------------------------------ATTACK ANIMATION MONTAGES------------------------------------

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj0(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/AnimMontages/Standing_1H_Magic_Attack_01_Montage.Standing_1H_Magic_Attack_01_Montage'"));
	if (MyAnimMontageObj0.Succeeded()) {
		Attack1 = MyAnimMontageObj0.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj1(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/AnimMontages/Standing_1H_Magic_Attack_01_Reverse_Montage.Standing_1H_Magic_Attack_01_Reverse_Montage'"));
	if (MyAnimMontageObj1.Succeeded()) {
		Attack2 = MyAnimMontageObj1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj2(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/AnimMontages/Standing_1H_Magic_Attack_02_Montage.Standing_1H_Magic_Attack_02_Montage'"));
	if (MyAnimMontageObj2.Succeeded()) {
		Attack3 = MyAnimMontageObj2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj3(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/Standing_2H_Magic_Attack_02_Montage.Standing_2H_Magic_Attack_02_Montage'"));
	if (MyAnimMontageObj3.Succeeded()) {
		Ability1Anim = MyAnimMontageObj3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj4(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/AnimMontages/Standing_1H_Magic_Attack_03_Montage.Standing_1H_Magic_Attack_03_Montage'"));
	if (MyAnimMontageObj4.Succeeded()) {
		Ability2Anim = MyAnimMontageObj4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>MyAnimMontageObj5(TEXT("AnimMontage'/Game/MageCharacterOffensive/Animations/AnimMontages/Standing_2H_Magic_Attack_01_Montage.Standing_2H_Magic_Attack_01_Montage'"));
	if (MyAnimMontageObj5.Succeeded()) {
		Ability3Anim = MyAnimMontageObj5.Object;
	}

	//------------------------------------------------------------------------------------------------

	//------------------------------------PARTICLE SYSTEMS--------------------------------------------


	//------------------------------------------------------------------------------------------------
}

void ADeathVeinCharacter::CoolDownDelay()
{
	if(CoolDown <= 7.f) {
		CoolDown += 1.f;
	}
	if (CoolDown1 <= 5.f) {
		CoolDown1 += 1.f;
	}
	if (CoolDown2 <= 30.f) {
		CoolDown2 += 1.f;
	}
}

//void ADeathVeinCharacter::MagicCircleSpawn()
//{
//	//Using Magic Circle
//	APlayerController* PlayerCont = (APlayerController*)UGameplayStatics::GetPlayerController(this, 0);
//
//	MagicCircleMeshComp->SetHiddenInGame(false);
//
//	FHitResult hitResult;
//	bool ishit = PlayerCont->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
//	if (ishit) {
//		hitResult.Location.Z = GetActorLocation().Z;
//		MagicCircleMeshComp->SetWorldLocation(hitResult.Location);
//		//MagicCircleMeshComp->SetRelativeLocation(hitResult.Location);
//	}
//}

//void ADeathVeinCharacter::CoolDownDelay1()
//{
//	
//}
//
//void ADeathVeinCharacter::CoolDownDelay2()
//{
//	
//}

//////////////////////////////////////////////////////////////////////////
// Input

void ADeathVeinCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("RollDodge", IE_Pressed, this, &ADeathVeinCharacter::StartRollDodge);
	PlayerInputComponent->BindAction("RollDodge", IE_Released, this, &ADeathVeinCharacter::StopRollDodge);

	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &ADeathVeinCharacter::LockOn);
	PlayerInputComponent->BindAction("LockOn", IE_Released, this, &ADeathVeinCharacter::StopLockOn);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ADeathVeinCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ADeathVeinCharacter::StopPrimaryAttack);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ADeathVeinCharacter::OpenCloseInventory);
	PlayerInputComponent->BindAction("Shop", IE_Pressed, this, &ADeathVeinCharacter::OpenCloseShop);

	PlayerInputComponent->BindAction("ItemUse1", IE_Pressed, this, &ADeathVeinCharacter::PrimaryItemUse);
	PlayerInputComponent->BindAction("ItemUse2", IE_Pressed, this, &ADeathVeinCharacter::SecondaryItemUse);

	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &ADeathVeinCharacter::PrimaryAbility);
	PlayerInputComponent->BindAction("SecondaryAbility", IE_Pressed, this, &ADeathVeinCharacter::SecondaryAbility);
	PlayerInputComponent->BindAction("ThirdAbility", IE_Pressed, this, &ADeathVeinCharacter::ThirdAbility);
	PlayerInputComponent->BindAction("FourthAbility", IE_Pressed, this, &ADeathVeinCharacter::FourthAbility);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADeathVeinCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADeathVeinCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADeathVeinCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADeathVeinCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADeathVeinCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADeathVeinCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADeathVeinCharacter::OnResetVR);
}


void ADeathVeinCharacter::ResetAttack()
{
	count = 0;
	GetWorld()->GetTimerManager().ClearTimer(ResetAttackHandler);
}

//--------------------------------------NOT WORKING CORRECTLY--------------------------------
void ADeathVeinCharacter::DelayAttack()
{
	if (isAttacking1)
		isSimpleAttacking1 = true;
	else if (isAttacking2)
		isSimpleAttacking2 = true;
	else if (isAttacking3)
		isSimpleAttacking3 = true;
	/*else if (isAttacking4)
		isSimpleAttacking4 = true;*/
}
//-------------------------------------------------------------------------------------------

void ADeathVeinCharacter::OpenCloseShop()
{
	APlayerController* PlayerCont = (APlayerController*)UGameplayStatics::GetPlayerController(this, 0);

	if (!isShopOpen) {

		if (CurrentShopWidget != nullptr) {
			isShopOpen = true;
			CurrentShopWidget->AddToViewport();
			PlayerCont->bShowMouseCursor = true;
		}
	}

	else {
		CurrentShopWidget->RemoveFromViewport();
		isShopOpen = false;
		PlayerCont->bShowMouseCursor = false;
	}
}

void ADeathVeinCharacter::PrimaryItemUse()
{
	isItemUsed1 = true;
}

void ADeathVeinCharacter::SecondaryItemUse()
{
	isItemUsed2 = true;
}

void ADeathVeinCharacter::OpenCloseInventory()
{
	APlayerController* PlayerCont = (APlayerController*)UGameplayStatics::GetPlayerController(this, 0);

	if (!isInventoryOpen) {

		if (CurrentInventoryWidget != nullptr) {
			isInventoryOpen = true;
			CurrentInventoryWidget->AddToViewport();
			PlayerCont->bShowMouseCursor = true;
		}
	}

	else {
		CurrentInventoryWidget->RemoveFromViewport();
		isInventoryOpen = false;
		PlayerCont->bShowMouseCursor = false;
	}
}

//-------------------------------PRIMARY ATTACK------------------------------------
void ADeathVeinCharacter::PrimaryAttack()
{
	isAttacking = true;

	ManaCost = 50.f;

	if (!isUsingAbility1 && !isUsingAbility2 && CurrentMana >= ManaCost) 
	{
		if (count == 0) {
			//isAttacking1 = true;
			PlayAnimMontage(Attack1, AnimPlayTime, NAME_None);
			
			FActorSpawnParameters SpawnParams;
			FTransform trans = GetActorTransform();

			GetWorld()->SpawnActor(Fireball, &trans, SpawnParams);

			CurrentMana -= ManaCost;

			//GetWorld()->GetTimerManager().SetTimer(DelayHandler, this, &ADeathVeinCharacter::DelayAttack, .8f, false);

			Damage = FMath::RandRange(.1f, .2f);

			GetWorld()->GetTimerManager().SetTimer(ResetAttackHandler, this, &ADeathVeinCharacter::ResetAttack, 1.f, false);

			count++;
		}
		else if (count == 1) {
			//isAttacking2 = true;
			
			PlayAnimMontage(Attack2, AnimPlayTime, NAME_None);

			FActorSpawnParameters SpawnParams;
			FTransform trans = GetActorTransform();

			GetWorld()->SpawnActor(Fireball, &trans, SpawnParams);

			CurrentMana -= ManaCost;

			//GetWorld()->GetTimerManager().SetTimer(DelayHandler, this, &ADeathVeinCharacter::DelayAttack, .8f, false);

			Damage = FMath::RandRange(.1f, .2f);

			GetWorld()->GetTimerManager().SetTimer(ResetAttackHandler, this, &ADeathVeinCharacter::ResetAttack, 1.f, false);
			count++;
		}
		else if (count == 2) {
			//isAttacking3 = true;
			PlayAnimMontage(Attack1, AnimPlayTime, NAME_None);

			FActorSpawnParameters SpawnParams;
			FTransform trans = GetActorTransform();

			GetWorld()->SpawnActor(Fireball, &trans, SpawnParams);

			CurrentMana -= ManaCost;

			//GetWorld()->GetTimerManager().SetTimer(DelayHandler, this, &ADeathVeinCharacter::DelayAttack, .8f, false);

			Damage = FMath::RandRange(.1f, .2f);

			GetWorld()->GetTimerManager().SetTimer(ResetAttackHandler, this, &ADeathVeinCharacter::ResetAttack, 1.f, false);
			count++;
		}
		else if (count == 3) {
			PlayAnimMontage(Attack3, AnimPlayTime, NAME_None);

			FActorSpawnParameters SpawnParams;
			FTransform trans = GetActorTransform();

			GetWorld()->SpawnActor(WaveProjectile, &trans, SpawnParams);

			CurrentMana -= ManaCost;

			Damage = FMath::RandRange(.15f, .25f);

			count = 0;
		}
		else {
			count = 0;
		}
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("NOT ENOUGH MANA")));
		}
	}

	if (isUsingAbility1 && isAttacking) {
		newDecal->MagicAbilityUse();
	}
	else if (isUsingAbility2 && isAttacking) {
		newDecal->MagicAbilityUse1();
	}
}

void ADeathVeinCharacter::StopPrimaryAttack()
{
	isAttacking = false;
	//isUsingAbility = false;
	isUsingAbility1 = false;
	isUsingAbility2 = false;
}

//-------------------------------PRIMARY ATTACK END------------------------------------

//---------------------------------ABILITY SYSTEM--------------------------------------
void ADeathVeinCharacter::PrimaryAbility()
{
	//STORM ABILITY

	isUsingAbility = true;

	if (CoolDown >= 7.f)
	{
		if (CurrentMana >= ManaCost && isUsingAbility)
		{
			CurrentMana -= ManaCost;

			PlayAnimMontage(Ability1Anim, AnimPlayTime, NAME_None);

			FVector loc = GetActorLocation();

			FRotator rot = GetActorRotation();

			FActorSpawnParameters SpawnParams;

			GetWorld()->SpawnActor(StormProjectile, &loc, &rot, SpawnParams);
		
		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("NOT ENOUGH MANA")));
			}
		}
		CoolDown = 0.f;
		GetWorld()->GetTimerManager().SetTimer(CoolDownHandler, this, &ADeathVeinCharacter::CoolDownDelay, 1.f, true);
	}
	else if (CoolDown <= 6.9f) {
		ManaCost = 0;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Ability On CoolDown")));
		}
	}

}
void ADeathVeinCharacter::SecondaryAbility()
{
	//GROUND SPIKE

	if (CoolDown1 >= 5.f)
	{
		isUsingAbility1 = true;

		if (CurrentMana >= ManaCost1)
		{
			CurrentMana -= ManaCost1;

			PlayAnimMontage(Ability2Anim, AnimPlayTime, NAME_None);

			FVector loc = GetActorLocation();
		
			FRotator rot = GetActorRotation();

			FActorSpawnParameters SpawnParams;
			
			AActor* myActor = GetWorld()->SpawnActor(MagicDecal, &loc, &rot, SpawnParams);

			newDecal = (AMagicDecal*)myActor;

		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("NOT ENOUGH MANA")));
			}
		}

		CoolDown1 = 0.f;
		
		GetWorld()->GetTimerManager().SetTimer(CoolDownHandler1, this, &ADeathVeinCharacter::CoolDownDelay, 1.f, true);
	}
	else if (CoolDown1 <= 4.9f) {
		ManaCost = 0;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Ability On CoolDown")));
		}
		isUsingAbility1 = false;
	}
}
void ADeathVeinCharacter::ThirdAbility()
{
	//PASSIVE ARCANCE ABILITY
	isRegenMana = true;

	float ManaRegen = (Intelligence / 10.f);
	CurrentMana += ManaRegen;
}
void ADeathVeinCharacter::FourthAbility()
{
	//METEOR STRIKE
	
	if (CoolDown2 >= 30.f)
	{
		isUsingAbility2 = true;

		if (CurrentMana >= ManaCost2)
		{
			CurrentMana -= ManaCost2;

			PlayAnimMontage(Ability3Anim, AnimPlayTime, NAME_None);

			FVector loc = GetActorLocation();
		
			FRotator rot = GetActorRotation();

			FActorSpawnParameters SpawnParams;
		
			AActor* myActor = GetWorld()->SpawnActor(MagicDecal, &loc, &rot, SpawnParams);

			newDecal = (AMagicDecal*)myActor;

		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("NOT ENOUGH MANA")));
			}
		}

		CoolDown2 = 0.f;

		GetWorld()->GetTimerManager().SetTimer(CoolDownHandler2, this, &ADeathVeinCharacter::CoolDownDelay, 1.f, true);
	}
	else if (CoolDown2 <= 29.9f) {
		ManaCost = 0;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Ability On CoolDown")));
		}
		isUsingAbility2 = false;
	}
}

//---------------------------------ABILITY SYSTEM END--------------------------------------

void ADeathVeinCharacter::StartRollDodge()
{
	isRollDodge = true;
}

void ADeathVeinCharacter::StopRollDodge()
{
	isRollDodge = false;
}

void ADeathVeinCharacter::LockOn()
{
	isLooking = true;

	FHitResult hitResult;

	FVector Start = GetActorLocation();
	FVector End = (GetActorForwardVector() * 2000.f) + Start;

	GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.f, 5.f, 5.f);

	if (hitResult.bBlockingHit) {

		float pitch = GetController()->GetControlRotation().Pitch;
		float roll = GetController()->GetControlRotation().Roll;

		FRotator rott = UKismetMathLibrary::FindLookAtRotation(FollowCamera->GetComponentLocation(), hitResult.Location);
		FRotator rotat = FMath::RInterpTo(GetControlRotation(), rott, GetWorld()->GetDeltaSeconds(), 6.f);
		FRotator rot = FRotator(pitch, rotat.Yaw, roll);
		GetController()->SetControlRotation(rot);
	}
}

void ADeathVeinCharacter::StopLockOn()
{
	isLooking = false;
}

int ADeathVeinCharacter::GetCurrentLvl()
{
	return CurrentLevel;
}

int ADeathVeinCharacter::UpdateLvl(int XpGain)
{
	Exp += XpGain;

	if (Exp >= MaxExp) {

		isLeveledUp = true;

		CurrentLevel++;
		Exp -= MaxExp;
		MaxExp += 100;

		if (CurrentLevel > MaxLevel) {
			CurrentLevel = MaxLevel;
		}

		Strength = CurrentLevel * 100.f;
		Agility = CurrentLevel * 50.f; 
		Intelligence = CurrentLevel * 150.f;
		AnimPlayTime = 1.f + (CurrentLevel / 10);
	}

	return CurrentLevel;
}

void ADeathVeinCharacter::BeginPlay()
{
	Super::BeginPlay();

	isItemUsed1 = false;
	isItemUsed2 = false;

	if (InventoryWidget != nullptr) {
		CurrentInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidget, NAME_None);
	}

	if (ShopWidget != nullptr) {
		CurrentShopWidget = CreateWidget<UUserWidget>(GetWorld(), ShopWidget, NAME_None);
	}

	CurrentCoins = 0;

	//HEALTH AND MANA VARIABLE SETUP
	MaxHp = 400.f;
	CurrentHp = MaxHp;

	MaxMana = 600.f;
	CurrentMana = MaxMana;
	
	HealthResistance = 1;
	isArmorEquipped = false;
	Damage = 0.f;

	//ANIMATION SETUP
	count = 0;
	isRollDodge = false;
	AnimPlayTime = 1.f;
	isAttacking = false;

	//PLAYER STAT SETUP
	CurrentLevel = 1;
	Strength = 1.f;
	Agility = 1.f;
	Intelligence = 1.f;
	MaxLevel = 20;
	Exp = 0;
	MaxExp = 100;
	isLeveledUp = false;

	CoolDown = 7.f;
	CoolDown1 = 5.f;
	CoolDown2 = 30.f;

	ManaCost = 80.f;
	ManaCost1 = 100.f;
	ManaCost2 = 250.f;
}

void ADeathVeinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float HpRegen = (Strength / 10.f);
	CurrentHp += HpRegen;

	ThirdAbility();
}

//--------------------------------CUSTOMS---------------------------------------------


int ADeathVeinCharacter::GetCurrentCoins()
{
	return CurrentCoins;
}

int ADeathVeinCharacter::UpdateCoins(int CoinsGain)
{
	CurrentCoins += CoinsGain;
	if (isLeveledUp) {
		CurrentCoins += 10;
	}
	if (CurrentHp <= 0) {
		CurrentCoins = 0;	
	}

	return CurrentCoins;
}

//-------------------------------HEALTH AND MANA SYSTEM SETUP--------------------------
float ADeathVeinCharacter::GetCurrentHp()
{
	return (CurrentHp / MaxHp);
}

float ADeathVeinCharacter::UpdateHp(float HpTaken)
{
	if (isLeveledUp) {
		MaxHp += Strength;
	}

	CurrentHp -= HpTaken - (HpTaken * HealthResistance / 100); // Health Resistance can be 10, 20, 30...

	if (CurrentHp >= MaxHp) {
		CurrentHp = MaxHp;
	}
	else if (CurrentHp <= 0) {
		
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

		UE_LOG(LogTemp, Warning, TEXT("No HP"));
	}

	return CurrentHp;
}

float ADeathVeinCharacter::GetCurrentMana()
{
	return (CurrentMana / MaxMana);
}

float ADeathVeinCharacter::UpdateMana(float ManaTaken)
{
	MaxMana += Intelligence;

	CurrentMana -= ManaTaken;

	if (CurrentMana > MaxMana) {
		CurrentMana = MaxMana;
		return CurrentMana;
	}

	else if (CurrentMana <= 0.f) {
		return CurrentMana = 0.001f;
		UE_LOG(LogTemp, Warning, TEXT("No MANA"));
	}

	return CurrentMana;
}

//-------------------------------HEALTH AND MANA SYSTEM SETUP END--------------------------

//------------------------------------------------------------------------------------

void ADeathVeinCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADeathVeinCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADeathVeinCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADeathVeinCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADeathVeinCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADeathVeinCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADeathVeinCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
