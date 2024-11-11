// Copyright Epic Games, Inc. All Rights Reserved.

#include "EjerciciosGameMode.h"
#include "EjerciciosCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEjerciciosGameMode::AEjerciciosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
