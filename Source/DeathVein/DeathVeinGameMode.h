// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DeathVeinGameMode.generated.h"

UCLASS(minimalapi)
class ADeathVeinGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;

public:
	ADeathVeinGameMode();

	//WIDGET
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		TSubclassOf<class UUserWidget> CharacterWidget;

	UPROPERTY()
		class UUserWidget* CurrentCharacterWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> InventoryItems;

	UFUNCTION()
		void ArrayInitializer();

};



