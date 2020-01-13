// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DeathVeinGameMode.h"
#include "DeathVeinCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ADeathVeinGameMode::ADeathVeinGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

void ADeathVeinGameMode::ArrayInitializer()
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing array"));
	for (int i = 0; i <= 7; i++) {
		InventoryItems.Add(0);
	}
}

void ADeathVeinGameMode::BeginPlay() 
{
	Super::BeginPlay();

	if (CharacterWidget != nullptr) {
		CurrentCharacterWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterWidget, NAME_None);
	}

	if (CurrentCharacterWidget != nullptr) {
		CurrentCharacterWidget->AddToViewport();
	}

	ArrayInitializer();
	
}
