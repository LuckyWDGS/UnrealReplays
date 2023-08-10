#include "UnrealReplayBPFLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "Engine/DemoNetDriver.h"

void UUnrealReplayBPFLibrary::StartRecordingLuckyReplay(const UObject* WorldContextObject,FString ReplayName, FString FriendlyName)
{
    FriendlyName = FString::Printf(TEXT("Replay-%d-%d-%d"),
    FDateTime::Now().GetYear(), FDateTime::Now().GetMonth(), FDateTime::Now().GetDay());
    if(auto GI=UGameplayStatics::GetGameInstance(WorldContextObject)){
        GI->StartRecordingReplay(ReplayName, FriendlyName);
        UE_LOG(LogTemp, Display, TEXT("Started replay recording to '%s'"), *FriendlyName);
    }

}

void UUnrealReplayBPFLibrary::StopRecordingLuckyReplay(const UObject* WorldContextObject)
{
    if (auto GI = UGameplayStatics::GetGameInstance(WorldContextObject)) {
        GI->StopRecordingReplay();
        UE_LOG(LogTemp, Display, TEXT("Finished replay recording!"));
    }
}

void UUnrealReplayBPFLibrary::PlayLuckyReplay(const UObject* WorldContextObject,FString ReplayName)
{
    if (auto GI = UGameplayStatics::GetGameInstance(WorldContextObject)) {
        GI->PlayReplay(ReplayName);
        UE_LOG(LogTemp, Display, TEXT("Playing replay recording from '%s'"), *ReplayName);
    }
}

TArray<FString> UUnrealReplayBPFLibrary::GetAllLuckyReplays()
{
    TArray<FString> AllReplays;
    FString ReplayPath = UKismetSystemLibrary::GetProjectSavedDirectory() + "Demos";
    IFileManager::Get().FindFilesRecursive(AllReplays, *ReplayPath, TEXT("*.replay*"), true, false);
    return AllReplays;
}

void UUnrealReplayBPFLibrary::RenameLuckyReplay(const FString& ReplayName, const FString& NewFriendlyReplayName)
{
}

void UUnrealReplayBPFLibrary::DeleteLuckyReplay(const FString& ReplayName)
{

}

void UUnrealReplayBPFLibrary::GotoTimeInSeconds(const UObject* WorldContextObject, float time)
{
    // If the playback is playing, tell the demo net driver to skip to the given time
    UDemoNetDriver* NetDriver = WorldContextObject->GetWorld()->DemoNetDriver;
    if (NetDriver->IsPlaying())
    {
        NetDriver->GotoTimeInSeconds(time / 1000.f);
    }

}

void UUnrealReplayBPFLibrary::SetPlaybackPlayRate(const UObject* WorldContextObject, float time)
{
    UDemoNetDriver* NetDriver = WorldContextObject->GetWorld()->DemoNetDriver;
    if (NetDriver->IsPlaying())
    {
        NetDriver->GotoTimeInSeconds(time / 1000.f);
        WorldContextObject->GetWorld()->GetWorldSettings()->DemoPlayTimeDilation = time;
    }
}

int UUnrealReplayBPFLibrary::GetCurrentTimeInMs(const UObject* WorldContextObject)
{
    // If the world, and demo net driver is valid, 
    UDemoNetDriver* NetDriver= WorldContextObject->GetWorld()->DemoNetDriver;
    if (NetDriver)
    {
        // Return the current time * 1000 (for s -> ms conversion)
        return NetDriver->DemoCurrentTime * 1000;
    }
    return 0;
}
