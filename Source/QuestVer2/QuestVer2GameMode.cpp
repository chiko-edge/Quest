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

	//�^�C�}�[�Z�b�g
	SetTimer();
}

void AQuestVer2GameMode::SetTimer() {
	//�^�C�}�[�J������
	FTimerManager& TimeManager = GetWorldTimerManager();
	//�^�C�}�[
	TimeManager.SetTimer(Handle, this, &AQuestVer2GameMode::TimeOver, MaxTime, false);
}

void AQuestVer2GameMode::TimeOver() {
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"Time Over");
	AQuestVer2Character* QuestVer2Character = Cast<AQuestVer2Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	//�^�C�}�[�J������
	FTimerManager& TimeManager = GetWorldTimerManager();
	TimeManager.ClearTimer(Handle);
	TimeManager.ClearAllTimersForObject(this);

	//�v���C���[���X�^�[�g
	QuestVer2Character->CallRestartPlayer();
}


/**
* �v���C���[�̃��X�|�[��
*/
void AQuestVer2GameMode::RestartPlayer(AController* NewPlayer) {
	Super::RestartPlayer(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"RestartPlayer call");
	SetTimer();
}

void AQuestVer2GameMode::PlayerDied(ACharacter* Character) {
	//�L�����N�^�[�R���g���[���[�ւ̎Q�Ƃ��擾
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);

	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"PlayerDied call");
}