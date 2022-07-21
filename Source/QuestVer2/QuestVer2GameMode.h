// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QuestVer2GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

UCLASS(minimalapi)
class AQuestVer2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AQuestVer2GameMode();
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	virtual void RestartPlayer(AController* NewPlayer) override;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    //Called when Player character has died.
    UFUNCTION()
        virtual void PlayerDied(ACharacter* Character);

    //Signature to bind delegate. 
    UPROPERTY()
        FOnPlayerDiedSignature OnPlayerDied;

private:
    FTimerHandle Handle;
    void TimeOver();
    void SetTimer();



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxTime")
    float MaxTime = 10;

    UFUNCTION(BlueprintCallable, Category = "MyTimeFunc")
        float NowTimeCount();
    UFUNCTION(BlueprintCallable, Category = "MyTimeFunc")
        void TimerStop();
};



