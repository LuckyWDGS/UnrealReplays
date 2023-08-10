#include "UnrealReplayBPFLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "Engine/DemoNetDriver.h"

void UUnrealReplayBPFLibrary::StartRecordingReplay(const UObject* WorldContextObject,FString ReplayName)
{
    FString FriendlyName = FString::Printf(TEXT("Replay-%d-%d-%d"),
    FDateTime::Now().GetYear(), FDateTime::Now().GetMonth(), FDateTime::Now().GetDay());
    if(auto GI=UGameplayStatics::GetGameInstance(WorldContextObject)){
        GI->StartRecordingReplay(ReplayName, FriendlyName);
        UE_LOG(LogTemp, Display, TEXT("Started replay recording to '%s'"), *FriendlyName);
    }

}

void UUnrealReplayBPFLibrary::StopRecordingReplay(const UObject* WorldContextObject)
{
    if (auto GI = UGameplayStatics::GetGameInstance(WorldContextObject)) {
        GI->StopRecordingReplay();
        UE_LOG(LogTemp, Display, TEXT("Finished replay recording!"));
    }
}

void UUnrealReplayBPFLibrary::PlayPlayback(const UObject* WorldContextObject,FString ReplayName)
{
    if (auto GI = UGameplayStatics::GetGameInstance(WorldContextObject)) {
        GI->PlayReplay(ReplayName);
        UE_LOG(LogTemp, Display, TEXT("Playing replay recording from '%s'"), *ReplayName);
    }
}

void UUnrealReplayBPFLibrary::PlayReplay(const UObject* WorldContextObject)
{
    UUnrealReplayBPFLibrary* MyLibrary = Cast<UUnrealReplayBPFLibrary>(StaticClass()->GetDefaultObject());
    if (MyLibrary) {
        SetPlaybackPlayRate(WorldContextObject, MyLibrary->PlayRate);
        return;
    }
    SetPlaybackPlayRate(WorldContextObject, 1);
    return;
}

void UUnrealReplayBPFLibrary::PauseReplay(const UObject* WorldContextObject)
{
    WorldContextObject->GetWorld()->GetWorldSettings()->DemoPlayTimeDilation =0;
}

TArray<FString> UUnrealReplayBPFLibrary::GetAllReplays()
{
    TArray<FString> AllReplays;
    FString ReplayPath = UKismetSystemLibrary::GetProjectSavedDirectory() + "Demos";
    IFileManager::Get().FindFilesRecursive(AllReplays, *ReplayPath, TEXT("*.replay*"), true, false);
    return AllReplays;
}

bool UUnrealReplayBPFLibrary::RenameReplay(const FString& ReplayName, const FString& NewFriendlyReplayName)
{
    return IFileManager::Get().Move(*NewFriendlyReplayName, *ReplayName);
}

bool UUnrealReplayBPFLibrary::DeleteReplay(const FString& ReplayName)
{
    return IFileManager::Get().Delete(*ReplayName);
}

void UUnrealReplayBPFLibrary::GotoTimeInSeconds(const UObject* WorldContextObject, float time)
{
    // If the playback is playing, tell the demo net driver to skip to the given time
    UDemoNetDriver* NetDriver = WorldContextObject->GetWorld()->GetDemoNetDriver();
    if (NetDriver->IsPlaying())
    {
        NetDriver->GotoTimeInSeconds(time / 1000.f);
    }

}

void UUnrealReplayBPFLibrary::SetPlaybackPlayRate(const UObject* WorldContextObject, float time)
{
    WorldContextObject->GetWorld()->GetWorldSettings()->DemoPlayTimeDilation = time;
    UUnrealReplayBPFLibrary* MyLibrary = Cast<UUnrealReplayBPFLibrary>(StaticClass()->GetDefaultObject());
      if (MyLibrary) {
            MyLibrary->PlayRate = time;
      }
}

int UUnrealReplayBPFLibrary::GetCurrentTimeInMs(const UObject* WorldContextObject)
{
    // If the world, and demo net driver is valid, 
    UDemoNetDriver* NetDriver= WorldContextObject->GetWorld()->GetDemoNetDriver();
    if (NetDriver)
    {
        // Return the current time * 1000 (for s -> ms conversion)
        return NetDriver->GetDemoCurrentTime();
    }
    return 0;
}

int UUnrealReplayBPFLibrary::GetTotalTimeInMs(const UObject* WorldContextObject)
{
    // If the world, and demo net driver is valid, 
    UDemoNetDriver* NetDriver = WorldContextObject->GetWorld()->GetDemoNetDriver();
    if (NetDriver)
    {
        // Return the Total time * 1000 (for s -> ms conversion)
        return NetDriver->GetDemoTotalTime();
    }
    return 0;
}
