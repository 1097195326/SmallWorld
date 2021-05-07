//
//  GAppInstance.hpp
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once


#include "CoreMinimal.h"
#include "GameObjectClass.h"
#include "Misc/CoreDelegates.h"
#include "Engine/GameInstance.h"
#include "GAppInstance.generated.h"

typedef enum {
	ENotReachable = 0,
	EReachableViaWiFi,
	EReachableViaWWAN
} ENetworkStatus;

UCLASS()
class UNREALENGINEWRAP_API UGAppInstance : public UGameInstance, public GameObjectClass
{
    GENERATED_BODY()
protected:
    static UGAppInstance *  m_Instance;
public:
    

    static UGAppInstance * GetInstance();
    
    virtual void Init() override;
    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
	virtual void OnStart() override;
    virtual void Shutdown() override;
    
    virtual    void ApplicationWillEnterBackground();
    virtual    void ApplicationHasEnteredForeground();
    

    virtual	void OpenLevel(const FString & _levelName);

	//ENetworkStatus GetNetworkStatus();

private:
	

    void ApplicationWillEnterBackground_Hander();
    void ApplicationHasEnteredForeground_Hander();
};

