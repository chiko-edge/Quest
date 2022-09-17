// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGameInstance.h"

int32 UQuestGameInstance::SetScore(int count)
{
	ScoreCount += count;
	return ScoreCount;
}

int32 UQuestGameInstance::GetScore()
{
	return ScoreCount;
}

void UQuestGameInstance::ResetScore()
{
	ScoreCount = 0;
}
