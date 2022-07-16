// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestVer2GameMode.h"
#include "QuestVer2Character.h"
#include "UObject/ConstructorHelpers.h"

AQuestVer2GameMode::AQuestVer2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
