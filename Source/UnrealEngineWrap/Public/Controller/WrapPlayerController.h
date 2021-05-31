//
//  GPawnController.h
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameObjectClass.h"
#include "GameFramework/PlayerController.h"
#include "WrapPlayerController.generated.h"

UCLASS()
class UNREALENGINEWRAP_API AWrapPlayerController : public APlayerController, public GameObjectClass
{
    GENERATED_BODY()
    
public:
	// feng zhuang APawn ,override AActor Functions 
    virtual void PostInitializeComponents();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:

    
};

