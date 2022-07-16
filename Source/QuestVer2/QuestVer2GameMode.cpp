// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestVer2GameMode.h"
#include "QuestVer2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AQuestVer2GameMode::AQuestVer2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AQuestVer2GameMode::BeginPlay() {

	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"BeginPlay");
	Super::BeginPlay();

	//�f���Q�[�h���o�C���h����Ă��Ȃ��ꍇ
	//PlayerDied�̃o�C���h���s��
	if (!OnPlayerDied.IsBound()) {
		OnPlayerDied.AddDynamic(this, &AQuestVer2GameMode::PlayerDied);
	}

	//�^�C�}�[
	FTimerManager& timeManager = GetWorldTimerManager();
	timeManager.SetTimer(handle, this, &AQuestVer2GameMode::TimeOver, 5.0f, false);
}

void AQuestVer2GameMode::TimeOver() {
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"Time Over");
	APlayerController* aPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	RestartPlayer(aPlayerController);

	//�^�C�}�[�J������
	FTimerManager& timeManager = GetWorldTimerManager();
	timeManager.ClearTimer(handle);
	timeManager.ClearAllTimersForObject(this);
}


/**
* �v���C���[�̃��X�|�[��
*/
void AQuestVer2GameMode::RestartPlayer(AController* NewPlayer) {
	Super::RestartPlayer(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"RestartPlayer call");
}

void AQuestVer2GameMode::PlayerDied(ACharacter* Character) {
	//�L�����N�^�[�R���g���[���[�ւ̎Q�Ƃ��擾
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);

	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"PlayerDied call");
}