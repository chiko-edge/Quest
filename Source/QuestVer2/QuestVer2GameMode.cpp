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

	//デリゲードがバインドされていない場合
	//PlayerDiedのバインドを行う
	if (!OnPlayerDied.IsBound()) {
		OnPlayerDied.AddDynamic(this, &AQuestVer2GameMode::PlayerDied);
	}

	//タイマーセット
	SetTimer();
}

void AQuestVer2GameMode::SetTimer() {
	//タイマー開放処理
	FTimerManager& TimeManager = GetWorldTimerManager();
	//タイマー
	TimeManager.SetTimer(Handle, this, &AQuestVer2GameMode::TimeOver, MaxTime, false);
}

void AQuestVer2GameMode::TimeOver() {
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"Time Over");
	AQuestVer2Character* QuestVer2Character = Cast<AQuestVer2Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	//タイマー開放処理
	FTimerManager& TimeManager = GetWorldTimerManager();
	TimeManager.ClearTimer(Handle);
	TimeManager.ClearAllTimersForObject(this);

	//プレイヤーリスタート
	QuestVer2Character->CallRestartPlayer();
}


/**
* プレイヤーのリスポーン
*/
void AQuestVer2GameMode::RestartPlayer(AController* NewPlayer) {
	Super::RestartPlayer(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"RestartPlayer call");
	SetTimer();
}

void AQuestVer2GameMode::PlayerDied(ACharacter* Character) {
	//キャラクターコントローラーへの参照を取得
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);

	UE_LOG(LogTemp, Log, TEXT("=====output : %s"), L"PlayerDied call");
}