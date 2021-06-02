//
//  GAppInstance.cpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

//#include "GCore.h"
#include "WrapGameInstance.h"

#include "RenderUtils.h"

UWrapGameInstance *  UWrapGameInstance::m_Instance = nullptr;

UWrapGameInstance * UWrapGameInstance::GetInstance()
{
    return m_Instance;
}
void UWrapGameInstance::Init()
{
    Super::Init();
	UE_LOG(LogTemp, Log, TEXT("zhx : ---UWrapGameInstance::Init"));

}

void UWrapGameInstance::PostInitProperties()
{
    Super::PostInitProperties();
    UE_LOG(LogTemp, Log, TEXT("zhx : ---UWrapGameInstance::PostInitProperties"));
    
	On_Init();

    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UWrapGameInstance::ApplicationWillEnterBackground_Hander);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UWrapGameInstance::ApplicationHasEnteredForeground_Hander);

}
void UWrapGameInstance::BeginDestroy()
{
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.RemoveAll(this);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.RemoveAll(this);

	UE_LOG(LogTemp, Log, TEXT("zhx : ---UWrapGameInstance::BeginDestroy"));

	On_Delete();
    
	Super::BeginDestroy();
}
void UWrapGameInstance::OnStart()
{
	UE_LOG(LogTemp, Log, TEXT("zhx : ---UWrapGameInstance::OnStart"));

	On_Start();
}
void UWrapGameInstance::Shutdown()
{
    UE_LOG(LogTemp,Log,TEXT("zhx : --- UWrapGameInstance::Shutdown"));
	On_End();
    Super::Shutdown();
}
void UWrapGameInstance::ApplicationWillEnterBackground_Hander()
{
    ApplicationWillEnterBackground();
}
void UWrapGameInstance::ApplicationHasEnteredForeground_Hander()
{
    ApplicationHasEnteredForeground();
}
void UWrapGameInstance::ApplicationWillEnterBackground()
{
    
    
}
void UWrapGameInstance::ApplicationHasEnteredForeground()
{
    
}
void UWrapGameInstance::OpenLevel(const FString & _levelName)
{
	
}
//ENetworkStatus UWrapGameInstance::GetNetworkStatus()
//{
//	ENetworkStatus state = EReachableViaWWAN;
//	//return state;
//#if PLATFORM_IOS
//    Reachability *tekuba_net = [Reachability reachabilityWithHostName];
//    switch ([tekuba_net currentReachabilityStatus])
//    {
//    case NotReachable:
//        // 没有网络连接
//        state = ENotReachable;
//        break;
//    case ReachableViaWWAN:
//        // 使用2G/3G/4G网络
//        state = EReachableViaWWAN;
//        break;
//    case ReachableViaWiFi:
//        // 使用WiFi网络
//        state = EReachableViaWiFi;
//        break;
//    }
//#endif
//	return state;
//}
