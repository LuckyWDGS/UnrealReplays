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
	/*记录播放速率*/
	UPROPERTY()
		float PlayRate=1.0f;


	/** 从蓝图开始记录回放 ReplayName = 磁盘上的文件名, FriendlyName = 在UI中重播的名称 */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void StartRecordingReplay(const UObject* WorldContextObject, FString ReplayName);

	/** 开始记录一个运行的重播，并保存它，从蓝图   */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void StopRecordingReplay(const UObject* WorldContextObject);

	/** 开始回放录制  */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void PlayPlayback(const UObject* WorldContextObject, FString ReplayName);

	/** 播放回放  */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void PlayReplay(const UObject* WorldContextObject);

	/** 暂停回放  */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void PauseReplay(const UObject* WorldContextObject);

	/** 在硬盘寻找历史回放*/
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay")
		static TArray<FString> GetAllReplays();

	/** 对重播应用一个新的自定义名称.Replays  */
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay")
		static bool RenameReplay(const FString& ReplayName, const FString& NewFriendlyReplayName);

	/*删除录制的回放格式文件.Replays*/
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay")
		static bool  DeleteReplay(const FString& ReplayName);

	/*跳转到回放中提供的时间（以秒为单位）*/
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay",meta = (WorldContext = "WorldContextObject"))
		static void GotoTimeInSeconds(const UObject* WorldContextObject, float time);

	/*设置播放速率*/
	UFUNCTION(BlueprintCallable, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static void SetPlaybackPlayRate(const UObject* WorldContextObject, float time);

	/*获取当前回放的时间*/
	UFUNCTION(BlueprintPure, Category = "UnrealReplay",meta = (WorldContext = "WorldContextObject"))
		static int GetCurrentTimeInMs(const UObject* WorldContextObject);

	/*获取回放的总时长*/
	UFUNCTION(BlueprintPure, Category = "UnrealReplay", meta = (WorldContext = "WorldContextObject"))
		static int GetTotalTimeInMs(const UObject* WorldContextObject);

protected:


private:

};

