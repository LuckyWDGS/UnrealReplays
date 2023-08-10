// Copyright 2022 Dreamingpoet All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UnrealReplayType.generated.h"

/*回放系统结构体*/
USTRUCT(BlueprintType)
struct UNREALREPLAY_API FReplayInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString ReplayName;

	UPROPERTY(BlueprintReadOnly)
		FString FriendlyName;

	UPROPERTY(BlueprintReadOnly)
		FDateTime Timestamp;

	UPROPERTY(BlueprintReadOnly)
		int32 LengthInMS;

	UPROPERTY(BlueprintReadOnly)
		bool bIsValid;

	FReplayInfo(FString NewName, FString NewFriendlyName, FDateTime NewTimestamp, int32 NewLengthInMS)
	{
		ReplayName = NewName;
		FriendlyName = NewFriendlyName;
		Timestamp = NewTimestamp;
		LengthInMS = NewLengthInMS;
		bIsValid = true;
	}

	FReplayInfo()
	{
		ReplayName = "Replay";
		FriendlyName = "Replay";
		Timestamp = FDateTime::MinValue();
		LengthInMS = 0;
		bIsValid = false;
	}
};