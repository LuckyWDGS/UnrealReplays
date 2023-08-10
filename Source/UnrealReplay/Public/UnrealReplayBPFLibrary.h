// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UnrealReplayType.h"
#include "NetworkReplayStreaming.h"
#include "UnrealReplayBPFLibrary.generated.h"


UCLASS()
class UNREALREPLAY_API UUnrealReplayBPFLibrary : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public: 
	/** 从蓝图开始记录回放 ReplayName = 磁盘上的文件名, FriendlyName = 在UI中重播的名称 */
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays", meta = (WorldContext = "WorldContextObject"))
		static void StartRecordingLuckyReplay(const UObject* WorldContextObject, FString ReplayName, FString FriendlyName);

	/** 开始记录一个运行的重播，并保存它，从蓝图   */
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays", meta = (WorldContext = "WorldContextObject"))
		static void StopRecordingLuckyReplay(const UObject* WorldContextObject);

	/** 开始回放以前录制的回放，从蓝图  */
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays", meta = (WorldContext = "WorldContextObject"))
		static void PlayLuckyReplay(const UObject* WorldContextObject, FString ReplayName);

	/** 开始在硬盘寻找历史回放*/
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays")
		static TArray<FString> GetAllLuckyReplays();

	/** 对重播应用一个新的自定义名称(仅适用于UI)  */
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays")
		static void RenameLuckyReplay(const FString& ReplayName, const FString& NewFriendlyReplayName);

	/*删除录制的回放格式文件.Replays*/
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays")
		static void  DeleteLuckyReplay(const FString& ReplayName);

	/*跳转到回放中提供的时间（以秒为单位）*/
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays",meta = (WorldContext = "WorldContextObject"))
		static void GotoTimeInSeconds(const UObject* WorldContextObject, float time);

	/*跳转到回放中提供的时间（以秒为单位）*/
	UFUNCTION(BlueprintCallable, Category = "LuckyReplays", meta = (WorldContext = "WorldContextObject"))
		static void SetPlaybackPlayRate(const UObject* WorldContextObject, float time);

	UFUNCTION(BlueprintPure, Category = "LuckyReplays",meta = (WorldContext = "WorldContextObject"))
		int GetCurrentTimeInMs(const UObject* WorldContextObject);

protected:


private:

};

