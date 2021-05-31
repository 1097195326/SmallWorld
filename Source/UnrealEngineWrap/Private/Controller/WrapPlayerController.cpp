//
//  GPawnController.c
//  GameFrame
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

//#include "GCore.h"
#include "WrapPlayerController.h"


void AWrapPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    On_Init();
}
void AWrapPlayerController::BeginPlay()
{
    Super::BeginPlay();

    On_Start();
}
void AWrapPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    On_Tick(DeltaSeconds);
}
void AWrapPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    On_End();
}
