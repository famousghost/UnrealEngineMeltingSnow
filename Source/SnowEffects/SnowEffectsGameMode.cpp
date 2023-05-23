// Copyright Epic Games, Inc. All Rights Reserved.

#include "SnowEffectsGameMode.h"
#include "SnowEffectsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASnowEffectsGameMode::ASnowEffectsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
