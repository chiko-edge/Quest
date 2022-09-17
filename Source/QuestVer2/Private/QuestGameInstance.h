// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "QuestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UQuestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ScoreCount = 0;

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 SetScore(int count);

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetScore();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ResetScore();

};
