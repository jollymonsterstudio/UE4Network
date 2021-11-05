// Copyright Epic Games, Inc. All Rights Reserved.

#include "Network1GameMode.h"
#include "Network1Character.h"
#include "UObject/ConstructorHelpers.h"

ANetwork1GameMode::ANetwork1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
